#!/usr/bin/env python3
"""
Generate a self-contained HTML progress dashboard for the xd-decomp project.
Parses configure.py without importing it (regex-based, no build required).

Usage:
    python tools/gen_progress_html.py
    python tools/gen_progress_html.py --version NXXJ01
    python tools/gen_progress_html.py --output my_progress.html
    python tools/gen_progress_html.py --no-report
"""

import argparse
import json
import re
from datetime import datetime
from pathlib import Path

VERSIONS = ["GXXE01", "NXXJ01"]

# Patterns for library block headers
_RE_DOLPHIN_REL = re.compile(r'(?:DolphinLib|Rel)\s*\(\s*"([^"]+)"')
_RE_MUSYX = re.compile(r'\bMusyX\s*\(')
_RE_DICT_LIB = re.compile(r'"lib"\s*:\s*"([^"]+)"')

# Pattern for Object() calls — captures the first positional argument (status token)
_RE_OBJECT = re.compile(
    r'\bObject\s*\(\s*(MatchingFor\s*\([^)]*\)|Matching|NonMatching|Equivalent|True|False)'
)
_RE_MF_VERSIONS = re.compile(r'"([^"]+)"')


def _parse_status(status_str: str, version: str) -> str:
    """Map a raw status token to 'matching', 'nonmatching', or 'equivalent'."""
    if status_str in ("Matching", "True"):
        return "matching"
    if status_str in ("NonMatching", "False"):
        return "nonmatching"
    if status_str == "Equivalent":
        return "equivalent"
    if status_str.startswith("MatchingFor"):
        paren = re.search(r'\(([^)]*)\)', status_str)
        if paren:
            versions = _RE_MF_VERSIONS.findall(paren.group(1))
            return "matching" if version in versions else "nonmatching"
    return "nonmatching"


def parse_configure(configure_path: Path, version: str) -> list:
    """
    Parse configure.py and return an ordered list of
    (lib_name, {"matching": int, "nonmatching": int, "equivalent": int}).
    """
    text = configure_path.read_text(encoding="utf-8")

    libs_start = text.find("config.libs = [")
    if libs_start == -1:
        raise ValueError("Could not find 'config.libs = [' in configure.py")

    # Only scan the libs section to avoid false matches in helper definitions above
    snippet = text[libs_start:]

    # Collect (position, kind, value) events from the libs section
    events = []

    # DolphinLib("name", ...) and Rel("name", ...) — name may be on the next line
    for m in _RE_DOLPHIN_REL.finditer(snippet):
        events.append((m.start(), "lib", m.group(1)))

    # MusyX(...) — lib name is always "musyx"
    for m in _RE_MUSYX.finditer(snippet):
        events.append((m.start(), "lib", "musyx"))

    # {"lib": "name", ...} — explicit dict-style lib blocks
    for m in _RE_DICT_LIB.finditer(snippet):
        events.append((m.start(), "lib", m.group(1)))

    # Object(status, ...) calls
    for m in _RE_OBJECT.finditer(snippet):
        status = _parse_status(m.group(1).strip(), version)
        events.append((m.start(), "obj", status))

    # Sort all events by position, then run a state machine
    events.sort(key=lambda e: e[0])

    libs: dict = {}
    lib_order: list = []
    current_lib = None

    for _pos, kind, value in events:
        if kind == "lib":
            current_lib = value
            if current_lib not in libs:
                libs[current_lib] = {"matching": 0, "nonmatching": 0, "equivalent": 0}
                lib_order.append(current_lib)
        else:  # "obj"
            if current_lib is not None:
                libs[current_lib][value] += 1

    return [(name, libs[name]) for name in lib_order]


def load_report(report_path: Path):
    """Load report.json if present; return None on any failure."""
    if not report_path.exists():
        return None
    try:
        with report_path.open(encoding="utf-8") as f:
            return json.load(f)
    except (json.JSONDecodeError, OSError):
        return None


def _pct(num, den) -> str:
    n, d = int(num), int(den)
    return f"{100 * n / d:.1f}" if d else "0.0"


def render_html(lib_data: list, version: str, report=None) -> str:
    """Return a complete self-contained HTML string."""
    config_total = {"matching": 0, "nonmatching": 0, "equivalent": 0}
    for _, counts in lib_data:
        for k in config_total:
            config_total[k] += counts[k]

    total_objs = sum(config_total.values())
    generated = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    headline_pct = "0.0"
    headline_label = "objects marked matching"
    donut = {
        "labels": ["Matching", "NonMatching", "Equivalent"],
        "values": [
            config_total["matching"],
            config_total["nonmatching"],
            config_total["equivalent"],
        ],
        "colors": ["#4caf50", "#f44336", "#ff9800"],
    }
    donut_title = "Overall configure status"
    bar_title = "configure.py status by library"
    stats_html = ""

    # Optional stats row from report.json
    if report:
        measures = report.get("measures", {})
        code_matched = measures.get("matched_code", 0)
        code_total = measures.get("total_code", 0)
        data_matched = measures.get("matched_data", 0)
        data_total = measures.get("total_data", 0)
        fn_matched = measures.get("matched_functions", 0)
        fn_total = measures.get("total_functions", 0)
        complete_units = measures.get("complete_units", 0)
        total_units = measures.get("total_units", total_objs)

        headline_pct = _pct(complete_units, total_units)
        headline_label = "objects linked"
        donut = {
            "labels": ["Linked", "Remaining"],
            "values": [int(complete_units), int(total_units) - int(complete_units)],
            "colors": ["#4caf50", "#30363d"],
        }
        donut_title = "Overall linked-object progress"

        stats_html = f"""<div class="stats-row">
  <div class="stat-card">
    <div class="stat-value">{_pct(code_matched, code_total)}%</div>
    <div class="stat-label">Code matched</div>
  </div>
  <div class="stat-card">
    <div class="stat-value">{fn_matched}/{fn_total}</div>
    <div class="stat-label">Functions matched</div>
  </div>
  <div class="stat-card">
    <div class="stat-value">{_pct(data_matched, data_total)}%</div>
    <div class="stat-label">Data matched</div>
  </div>
  <div class="stat-card">
    <div class="stat-value">{complete_units}/{total_units}</div>
    <div class="stat-label">Objects linked</div>
  </div>
  <div class="stat-card">
    <div class="stat-value">{config_total["matching"] + config_total["equivalent"]}/{total_objs}</div>
    <div class="stat-label">Objects marked matching/equivalent</div>
  </div>
</div>"""
    else:
        headline_pct = _pct(config_total["matching"] + config_total["equivalent"], total_objs)
        stats_html = f"""<div class="stats-row">
  <div class="stat-card">
    <div class="stat-value">{config_total["matching"] + config_total["equivalent"]}/{total_objs}</div>
    <div class="stat-label">Objects marked matching/equivalent</div>
  </div>
</div>"""

    # Per-lib bar data — sorted largest-total-first
    sorted_libs = sorted(lib_data, key=lambda x: sum(x[1].values()), reverse=True)

    data_obj = {
        "version": version,
        "generated": generated,
        "config_total": config_total,
        "donut": donut,
        "bar": {
            "labels":      [name for name, _ in sorted_libs],
            "matching":    [counts["matching"]    for _, counts in sorted_libs],
            "nonmatching": [counts["nonmatching"] for _, counts in sorted_libs],
            "equivalent":  [counts["equivalent"]  for _, counts in sorted_libs],
        },
    }
    data_json = json.dumps(data_obj, ensure_ascii=False)

    # The bar canvas height is computed in JS based on the number of libs.
    # We pre-compute an estimate here for the initial style.
    bar_h_est = max(300, len(sorted_libs) * 22 + 60)

    return f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Pok\u00e9mon XD Decompilation Progress \u2014 {version}</title>
<script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.0/dist/chart.umd.min.js"></script>
<style>
  *, *::before, *::after {{ box-sizing: border-box; margin: 0; padding: 0; }}
  body {{
    background: #0d1117;
    color: #e0e0e0;
    font-family: system-ui, -apple-system, sans-serif;
    padding: 28px;
    min-height: 100vh;
  }}
  h1 {{ font-size: 1.55rem; margin-bottom: 4px; }}
  .subtitle {{ color: #888; font-size: 0.875rem; margin-bottom: 28px; }}
  .stats-row {{
    display: flex;
    gap: 14px;
    flex-wrap: wrap;
    margin-bottom: 32px;
  }}
  .stat-card {{
    background: #161b22;
    border: 1px solid #30363d;
    border-radius: 8px;
    padding: 16px 24px;
    min-width: 150px;
    text-align: center;
  }}
  .stat-value {{ font-size: 1.75rem; font-weight: 700; color: #58a6ff; }}
  .stat-label {{ font-size: 0.78rem; color: #888; margin-top: 4px; }}
  .charts-row {{
    display: flex;
    gap: 28px;
    flex-wrap: wrap;
    align-items: flex-start;
  }}
  .chart-box {{
    background: #161b22;
    border: 1px solid #30363d;
    border-radius: 8px;
    padding: 20px;
  }}
  .chart-title {{
    font-size: 0.9rem;
    font-weight: 600;
    color: #c9d1d9;
    margin-bottom: 14px;
  }}
  #bar-box {{
    flex: 1;
    min-width: 480px;
    overflow-x: auto;
  }}
  #bar-wrap {{
    position: relative;
    height: {bar_h_est}px;
    min-width: 400px;
  }}
</style>
</head>
<body>
<h1>Pok\u00e9mon XD: Gale of Darkness \u2014 Decompilation Progress</h1>
<p class="subtitle">{version}&nbsp;&nbsp;\u00b7&nbsp;&nbsp;{headline_pct}% {headline_label}&nbsp;&nbsp;\u00b7&nbsp;&nbsp;Generated {generated}</p>
{stats_html}
<div class="charts-row">
  <div class="chart-box">
    <div class="chart-title">{donut_title}</div>
    <canvas id="donut" width="300" height="300"></canvas>
  </div>
  <div class="chart-box" id="bar-box">
    <div class="chart-title">{bar_title}</div>
    <div id="bar-wrap"><canvas id="bar"></canvas></div>
  </div>
</div>

<script>
const DATA = {data_json};

// ── Donut chart ──────────────────────────────────────────────────────────────
new Chart(document.getElementById('donut'), {{
  type: 'doughnut',
  data: {{
    labels: DATA.donut.labels,
    datasets: [{{
      data: DATA.donut.values,
      backgroundColor: DATA.donut.colors,
      borderWidth: 2,
      borderColor: '#161b22',
    }}],
  }},
  options: {{
    responsive: false,
    plugins: {{
      legend: {{
        position: 'bottom',
        labels: {{ color: '#e0e0e0', padding: 16 }},
      }},
      tooltip: {{
        callbacks: {{
          label: function(ctx) {{
            const tot = ctx.dataset.data.reduce((a, b) => a + b, 0);
            const pct = (ctx.parsed / tot * 100).toFixed(1);
            return ' ' + ctx.label + ': ' + ctx.parsed + ' (' + pct + '%)';
          }},
        }},
      }},
    }},
  }},
}});

// ── Horizontal stacked bar ───────────────────────────────────────────────────
const barH = Math.max(300, DATA.bar.labels.length * 22 + 60);
document.getElementById('bar-wrap').style.height = barH + 'px';

new Chart(document.getElementById('bar'), {{
  type: 'bar',
  data: {{
    labels: DATA.bar.labels,
    datasets: [
      {{
        label: 'Matching',
        data: DATA.bar.matching,
        backgroundColor: '#4caf50',
      }},
      {{
        label: 'Equivalent',
        data: DATA.bar.equivalent,
        backgroundColor: '#ff9800',
      }},
      {{
        label: 'NonMatching',
        data: DATA.bar.nonmatching,
        backgroundColor: '#f44336',
      }},
    ],
  }},
  options: {{
    indexAxis: 'y',
    responsive: true,
    maintainAspectRatio: false,
    scales: {{
      x: {{
        stacked: true,
        ticks: {{ color: '#888' }},
        grid: {{ color: '#21262d' }},
      }},
      y: {{
        stacked: true,
        ticks: {{ color: '#e0e0e0', font: {{ size: 11 }} }},
        grid: {{ color: '#21262d' }},
      }},
    }},
    plugins: {{
      legend: {{
        position: 'bottom',
        labels: {{ color: '#e0e0e0', padding: 12 }},
      }},
      tooltip: {{
        callbacks: {{
          afterTitle: function(items) {{
            const i = items[0].dataIndex;
            const tot = DATA.bar.matching[i] + DATA.bar.nonmatching[i] + DATA.bar.equivalent[i];
            const matched = DATA.bar.matching[i] + DATA.bar.equivalent[i];
            const pct = tot ? (matched / tot * 100).toFixed(1) : '0.0';
            return 'Configured matching/equivalent: ' + pct + '%';
          }},
        }},
      }},
    }},
  }},
}});
</script>
</body>
</html>
"""


def main():
    parser = argparse.ArgumentParser(
        description="Generate a progress dashboard HTML for the xd-decomp project."
    )
    parser.add_argument(
        "--version", "-v",
        choices=VERSIONS,
        default=VERSIONS[0],
        type=str.upper,
        help=f"game version to report on (default: {VERSIONS[0]})",
    )
    parser.add_argument(
        "--output", "-o",
        type=Path,
        default=Path("progress.html"),
        help="output HTML file (default: progress.html)",
    )
    parser.add_argument(
        "--no-report",
        action="store_true",
        help="skip report.json lookup even if present",
    )
    parser.add_argument(
        "--configure",
        type=Path,
        default=Path("configure.py"),
        help="path to configure.py (default: configure.py)",
    )
    args = parser.parse_args()

    lib_data = parse_configure(args.configure, args.version)

    report = None
    if not args.no_report:
        report_path = Path(f"build/{args.version}/report.json")
        report = load_report(report_path)
        if report:
            print(f"Loaded report from {report_path}")

    html = render_html(lib_data, args.version, report)
    args.output.write_text(html, encoding="utf-8")

    total_objs = sum(sum(c.values()) for _, c in lib_data)
    total_m = sum(c["matching"] for _, c in lib_data)
    total_nm = sum(c["nonmatching"] for _, c in lib_data)
    total_eq = sum(c["equivalent"] for _, c in lib_data)

    print(f"Written to {args.output}")
    if report:
        measures = report.get("measures", {})
        print(
            f"  Linked objects: {measures.get('complete_units', 0)}/{measures.get('total_units', total_objs)} "
            f"({_pct(measures.get('complete_units', 0), measures.get('total_units', total_objs))}%)"
        )
    print(
        f"  Configure status: {total_objs} total | {total_m} Matching | "
        f"{total_nm} NonMatching | {total_eq} Equivalent"
    )


if __name__ == "__main__":
    main()
