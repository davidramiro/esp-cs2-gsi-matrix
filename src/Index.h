#pragma once
const char idx1[] PROGMEM = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" />
    <title>CS2 GSI Screen</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
        :root {
            --bg: #050816;
            --bg-alt: #0b1020;
            --accent: #4ade80;
            --accent-soft: rgba(74, 222, 128, 0.12);
            --accent-strong: rgba(74, 222, 128, 0.28);
            --text: #e5e7eb;
            --muted: #9ca3af;
            --border: #1f2937;
            --code-bg: #020617;
            --danger: #f97373;
        }

        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

        body {
            font-family: system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
            background: radial-gradient(circle at top, #111827 0, #020617 55%, #000 100%);
            color: var(--text);
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 1.5rem;
        }

        .card {
            width: 100%;
            max-width: 880px;
            background: linear-gradient(145deg, rgba(15, 23, 42, 0.95), rgba(3, 7, 18, 0.98));
            border-radius: 18px;
            border: 1px solid rgba(55, 65, 81, 0.8);
            box-shadow:
                    0 24px 60px rgba(0, 0, 0, 0.85),
                    0 0 0 1px rgba(15, 23, 42, 0.9);
            overflow: hidden;
            backdrop-filter: blur(20px);
        }

        .header {
            position: relative;
            padding: 1.4rem 1.6rem 1.2rem;
            border-bottom: 1px solid rgba(31, 41, 55, 0.9);
            background:
                    radial-gradient(circle at 0 0, rgba(74, 222, 128, 0.26), transparent 55%),
                    radial-gradient(circle at 95% 0, rgba(56, 189, 248, 0.26), transparent 55%),
                    linear-gradient(135deg, rgba(15, 23, 42, 0.96), rgba(15, 23, 42, 0.92));
        }

        .header::after {
            content: "";
            position: absolute;
            inset: 0;
            background-image: radial-gradient(circle at 0 0, rgba(148, 163, 184, 0.16), transparent 60%);
            mix-blend-mode: soft-light;
            opacity: 0.85;
            pointer-events: none;
        }

        .header-top {
            display: flex;
            align-items: center;
            justify-content: space-between;
            gap: 1rem;
            position: relative;
            z-index: 1;
        }

        .title-group {
            display: flex;
            flex-direction: column;
            gap: 0.15rem;
        }

        .badge-row {
            display: inline-flex;
            align-items: center;
            gap: 0.45rem;
            font-size: 0.75rem;
            text-transform: uppercase;
            letter-spacing: 0.12em;
            color: var(--muted);
        }

        .badge {
            padding: 0.12rem 0.5rem;
            border-radius: 999px;
            border: 1px solid rgba(148, 163, 184, 0.5);
            background: radial-gradient(circle at 0 0, rgba(74, 222, 128, 0.12), transparent 52%);
            color: var(--accent);
            font-weight: 600;
        }

        .title {
            font-size: 1.1rem;
            font-weight: 600;
            letter-spacing: 0.05em;
            text-transform: uppercase;
            color: #f9fafb;
        }

        .subtitle {
            font-size: 0.82rem;
            color: var(--muted);
        }

        .status-pill {
            display: inline-flex;
            align-items: center;
            gap: 0.4rem;
            padding: 0.32rem 0.7rem;
            border-radius: 999px;
            border: 1px solid rgba(34, 197, 94, 0.45);
            background: linear-gradient(135deg, rgba(22, 163, 74, 0.22), rgba(6, 95, 70, 0.32));
            color: #bbf7d0;
            font-size: 0.75rem;
            font-weight: 500;
            white-space: nowrap;
        }

        .status-dot {
            width: 7px;
            height: 7px;
            border-radius: 999px;
            background: #22c55e;
            box-shadow: 0 0 0 4px rgba(34, 197, 94, 0.45);
        }

        .status-pill small {
            color: rgba(209, 250, 229, 0.85);
            text-transform: uppercase;
            letter-spacing: 0.16em;
        }

        .main {
            padding: 1.3rem 1.6rem 1.5rem;
            display: grid;
            grid-template-columns: minmax(0, 1.6fr) minmax(0, 1fr);
            gap: 1.5rem;
        }

        @media (max-width: 800px) {
            .main {
                grid-template-columns: minmax(0, 1fr);
            }
        }

        .pane {
            border-radius: 14px;
            border: 1px solid var(--border);
            background: radial-gradient(circle at 0 0, rgba(148, 163, 184, 0.08), transparent 60%),
            linear-gradient(145deg, rgba(15, 23, 42, 0.95), rgba(15, 23, 42, 0.9));
            overflow: hidden;
        }

        .pane-header {
            padding: 0.75rem 1rem;
            border-bottom: 1px solid rgba(31, 41, 55, 0.9);
            display: flex;
            align-items: center;
            justify-content: space-between;
            gap: 0.6rem;
            background: linear-gradient(120deg, rgba(15, 23, 42, 0.95), rgba(3, 7, 18, 0.96));
        }

        .pane-header h2 {
            font-size: 0.86rem;
            letter-spacing: 0.16em;
            text-transform: uppercase;
            font-weight: 600;
            color: #e5e7eb;
        }

        .pane-header span {
            font-size: 0.75rem;
            color: var(--muted);
        }

        .pane-body {
            padding: 0.9rem 1rem 1rem;
        }

        .hint {
            font-size: 0.78rem;
            color: var(--muted);
            margin-bottom: 0.5rem;
        }

        pre {
            margin: 0;
            padding: 0.9rem 0.9rem 0.95rem;
            border-radius: 10px;
            background: radial-gradient(circle at 0 0, rgba(15, 23, 42, 0.98), rgba(2, 6, 23, 1));
            border: 1px solid rgba(30, 64, 175, 0.8);
            box-shadow: inset 0 0 0 1px rgba(15, 23, 42, 0.9);
            max-height: 360px;
            overflow: auto;
            font-size: 0.8rem;
            line-height: 1.4;
            color: #e5e7eb;
            position: relative;
        }

        code {
            font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;
            white-space: pre;
        }

        .toolbar {
            display: flex;
            flex-wrap: wrap;
            gap: 0.5rem;
            margin-top: 0.7rem;
        }

        button {
            appearance: none;
            border: none;
            cursor: pointer;
            border-radius: 999px;
            padding: 0.45rem 0.9rem;
            font-size: 0.8rem;
            font-weight: 500;
            letter-spacing: 0.05em;
            text-transform: uppercase;
            display: inline-flex;
            align-items: center;
            gap: 0.4rem;
            transition: transform 0.12s ease-out, box-shadow 0.12s ease-out, background 0.12s ease-out, border-color 0.12s ease-out;
            white-space: nowrap;
        }

        button.primary {
            background: radial-gradient(circle at 0 0, rgba(74, 222, 128, 0.35), transparent 55%),
            linear-gradient(135deg, #22c55e, #16a34a);
            color: #022c22;
            box-shadow:
                    0 10px 25px rgba(22, 163, 74, 0.55),
                    0 0 0 1px rgba(5, 46, 22, 0.85);
        }

        button.primary:hover {
            transform: translateY(-1px);
            box-shadow:
                    0 14px 30px rgba(22, 163, 74, 0.65),
                    0 0 0 1px rgba(6, 78, 59, 0.9);
        }

        button.secondary {
            background: linear-gradient(135deg, rgba(15, 23, 42, 0.95), rgba(3, 7, 18, 0.98));
            color: #e5e7eb;
            border: 1px solid rgba(148, 163, 184, 0.7);
            box-shadow:
                    0 6px 18px rgba(15, 23, 42, 0.95),
                    0 0 0 1px rgba(15, 23, 42, 1);
        }

        button.secondary:hover {
            background: linear-gradient(135deg, rgba(17, 24, 39, 1), rgba(3, 7, 18, 1));
        }

        button:active {
            transform: translateY(0);
            box-shadow: 0 0 0 1px rgba(15, 23, 42, 1);
        }

        .icon {
            width: 14px;
            height: 14px;
            border-radius: 4px;
            border: 1px solid rgba(15, 23, 42, 0.9);
            background: radial-gradient(circle at 0 0, rgba(248, 250, 252, 0.4), transparent 60%),
            linear-gradient(135deg, #e5e7eb, #94a3b8);
            display: inline-flex;
            align-items: center;
            justify-content: center;
            color: #020617;
            font-size: 10px;
            font-weight: 700;
        }

        .icon-download {
            width: 14px;
            height: 14px;
            border-radius: 50%;
            border: 1px solid rgba(15, 23, 42, 0.9);
            background: radial-gradient(circle at 0 0, rgba(248, 250, 252, 0.45), transparent 60%),
            linear-gradient(145deg, #f9fafb, #cbd5f5);
            display: inline-flex;
            align-items: center;
            justify-content: center;
            color: #020617;
            font-size: 10px;
            font-weight: 800;
        }

        .meta {
            display: grid;
            grid-template-columns: repeat(2, minmax(0, 1fr));
            gap: 0.6rem 0.9rem;
            font-size: 0.78rem;
            margin-bottom: 0.75rem;
        }

        .meta-item {
            display: flex;
            flex-direction: column;
            gap: 0.1rem;
        }

        .meta-label {
            text-transform: uppercase;
            letter-spacing: 0.16em;
            color: var(--muted);
            font-size: 0.7rem;
        }

        .meta-value {
            color: #e5e7eb;
        }

        .meta-value code {
            background: rgba(15, 23, 42, 0.9);
            padding: 0.08rem 0.35rem;
            border-radius: 999px;
            border: 1px solid rgba(31, 41, 55, 0.9);
            font-size: 0.74rem;
        }

        .note {
            margin-top: 0.4rem;
            padding: 0.55rem 0.7rem;
            border-radius: 10px;
            background: radial-gradient(circle at 0 0, var(--accent-soft), transparent 55%);
            border: 1px dashed rgba(55, 65, 81, 0.9);
            color: var(--muted);
            font-size: 0.76rem;
        }

        .note strong {
            color: #e5e7eb;
            font-weight: 600;
        }

        .footer {
            padding: 0.9rem 1.6rem 1rem;
            border-top: 1px solid rgba(31, 41, 55, 0.9);
            display: flex;
            flex-wrap: wrap;
            justify-content: space-between;
            gap: 0.8rem;
            font-size: 0.75rem;
            color: var(--muted);
            background: linear-gradient(180deg, rgba(15, 23, 42, 0.96), rgba(3, 7, 18, 1));
        }

        .footer span strong {
            color: #e5e7eb;
            font-weight: 600;
        }

        .footer small {
            color: rgba(148, 163, 184, 0.9);
        }

        .toast {
            position: fixed;
            inset-inline: 0;
            bottom: 1.3rem;
            display: flex;
            justify-content: center;
            pointer-events: none;
            z-index: 50;
        }

        .toast-inner {
            pointer-events: auto;
            padding: 0.5rem 0.85rem;
            border-radius: 999px;
            border: 1px solid rgba(34, 197, 94, 0.6);
            background: linear-gradient(135deg, rgba(21, 128, 61, 0.98), rgba(6, 95, 70, 0.98));
            color: #ecfdf3;
            font-size: 0.8rem;
            display: flex;
            align-items: center;
            gap: 0.4rem;
            box-shadow:
                    0 14px 40px rgba(22, 163, 74, 0.7),
                    0 0 0 1px rgba(6, 78, 59, 0.95);
            opacity: 0;
            transform: translateY(12px);
            pointer-events: none;
            transition: opacity 0.15s ease-out, transform 0.15s ease-out;
        }

        .toast.show .toast-inner {
            opacity: 1;
            transform: translateY(0);
            pointer-events: auto;
        }

        .toast-icon {
            width: 16px;
            height: 16px;
            border-radius: 999px;
            background: rgba(22, 163, 74, 0.1);
            border: 1px solid rgba(187, 247, 208, 0.9);
            display: inline-flex;
            align-items: center;
            justify-content: center;
            font-size: 11px;
        }

        .toast-error .toast-inner {
            border-color: rgba(248, 113, 113, 0.7);
            background: linear-gradient(135deg, rgba(239, 68, 68, 0.98), rgba(127, 29, 29, 0.98));
            box-shadow:
                    0 14px 40px rgba(248, 113, 113, 0.7),
                    0 0 0 1px rgba(127, 29, 29, 0.95);
        }

        .toast-error .toast-icon {
            border-color: rgba(254, 226, 226, 0.95);
            background: rgba(127, 29, 29, 0.45);
        }
    </style>
</head>
<body>
<div class="card">
    <header class="header">
        <div class="header-top">
            <div class="title-group">
                <div class="badge-row">
                    <span class="badge">CS2 Screen</span>
                    <span>Gamestate Integration Config</span>
                </div>
                <h1 class="title">gamestate_integration_cs2screen.cfg</h1>
                <p class="subtitle">Copy the config block below or download it as a ready-to-use CFG file.</p>
            </div>
            <div class="status-pill">
                <span class="status-dot"></span>
                <span>Ready to use</span>
            </div>
        </div>
    </header>

    <main class="main">
        <section class="pane">
            <div class="pane-header">
                <div>
                    <h2>Config File</h2>
                    <span>Copy &amp; paste into your CS2 cfg folder</span>
                </div>
            </div>
            <div class="pane-body">
                <pre id="cfgCode">"ESPCS2GSI Integration v1.0.0"
{
 "uri" "http://)";

const char idx2[] PROGMEM = R"("
 "timeout" "5.0"
 "buffer" "0.1"
 "throttle" "0.5"
 "heartbeat" "15.0"
 "data"
 {
   "round"          "1"
   "player_state"   "1"
 }
}</code></pre>
                <div class="toolbar">
                    <button class="primary" id="copyBtn" type="button">
                        <span class="icon">C</span>
                        <span>Copy to clipboard</span>
                    </button>
                    <button class="secondary" id="downloadBtn" type="button">
                        <span class="icon-download">↓</span>
                        <span>Download cfg file</span>
                    </button>
                </div>
            </div>
        </section>

        <aside class="pane">
            <div class="pane-header">
                <div>
                    <h2>How to use</h2>
                    <span>Basic setup</span>
                </div>
            </div>
            <div class="pane-body">
                <p class="hint">
                    1. Copy or download the file.<br /><br />
                    2. Place it in your CS2 config directory:<br /><br />
                    <code>game\csgo\cfg </code>
                    <br /> <br />
                    3. Restart the game.  <br /><br />
                </p>
                <div class="note">
                    <strong>Note:</strong> You can navigate to your game folder
                    by right-clicking CS2 on Steam -> Manage -> Browse Local Files.
                </div>
            </div>
        </aside>
    </main>

    <footer class="footer">
      <span>
        <strong>Hint:</strong> Filenames must start with <code>gamestate_integration_</code> for CS to load the config.
      </span>
        <span>
        <small>made with ❤️ by davidramiro</small>
      </span>
    </footer>
</div>

<div class="toast" id="toast">
    <div class="toast-inner" id="toastInner">
        <span class="toast-icon" id="toastIcon">✓</span>
        <span id="toastText">Copied to clipboard</span>
    </div>
</div>

<script>
    (function () {
        const cfgCode = document.getElementById("cfgCode");
        const copyBtn = document.getElementById("copyBtn");
        const downloadBtn = document.getElementById("downloadBtn");
        const toast = document.getElementById("toast");
        const toastInner = document.getElementById("toastInner");
        const toastIcon = document.getElementById("toastIcon");
        const toastText = document.getElementById("toastText");

        let toastTimer = null;

        function showToast(message, isError) {
            toastText.textContent = message;
            if (isError) {
                toast.classList.add("toast-error");
            } else {
                toast.classList.remove("toast-error");
            }
            requestAnimationFrame(() => {
                toast.classList.add("show");
            });

            if (toastTimer) clearTimeout(toastTimer);
            toastTimer = setTimeout(() => {
                toast.classList.remove("show");
            }, 2300);
        }

        function copyCfg() {
            const text = cfgCode.textContent || cfgCode.innerText;
            if (!navigator.clipboard || !navigator.clipboard.writeText) {
                try {
                    const range = document.createRange();
                    range.selectNodeContents(cfgCode);
                    const sel = window.getSelection();
                    sel.removeAllRanges();
                    sel.addRange(range);
                    const ok = document.execCommand("copy");
                    sel.removeAllRanges();
                    showToast(ok ? "Config copied" : "Copy failed", !ok);
                } catch (e) {
                    showToast("Copy not supported in this browser", true);
                }
                return;
            }

            navigator.clipboard
                .writeText(text)
                .then(() => {
                    showToast("Config copied", false);
                })
                .catch(() => {
                    showToast("Copy failed", true);
                });
        }

        function downloadCfg() {
            const blob = new Blob([cfgCode.textContent || cfgCode.innerText], {
                type: "text/plain;charset=utf-8",
            });
            const url = URL.createObjectURL(blob);
            const a = document.createElement("a");
            a.href = url;
            a.download = "gamestate_integration_cs2gsi.cfg";
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            URL.revokeObjectURL(url);
            showToast("Download started", false);
        }

        copyBtn.addEventListener("click", copyCfg);
        downloadBtn.addEventListener("click", downloadCfg);
    })();
</script>
</body>
</html>
)";