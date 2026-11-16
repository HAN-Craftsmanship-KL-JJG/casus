import { useEffect, useState } from "react";

interface Status {
  name: string;
  version: string;
  database: "ok" | "unavailable";
  message?: string;
}

type State = { kind: "loading" } | { kind: "loaded"; status: Status } | { kind: "failed" };

export function App() {
  const [state, setState] = useState<State>({ kind: "loading" });

  useEffect(() => {
    fetch("/api/status")
      .then((response) => response.json() as Promise<Status>)
      .then((status) => setState({ kind: "loaded", status }))
      .catch(() => setState({ kind: "failed" }));
  }, []);

  return (
    <main>
      <h1>ICDE</h1>
      <p>Integrated Course Design Environment</p>
      <p>Deze applicatie is in ontwikkeling.</p>
      <StatusList state={state} />
    </main>
  );
}

function StatusList({ state }: { state: State }) {
  if (state.kind === "loading") {
    return <p>Status ophalen...</p>;
  }
  if (state.kind === "failed") {
    return <p>De applicatieserver geeft geen antwoord.</p>;
  }
  const { status } = state;
  return (
    <dl>
      <dt>Applicatieserver</dt>
      <dd>
        {status.name} {status.version}
      </dd>
      <dt>Database</dt>
      <dd>{status.database === "ok" ? status.message : "niet bereikbaar"}</dd>
      <dt>Documentserver</dt>
      <dd>
        <a href="/api/example/pdf">Voorbeeld als PDF</a>
        {" of "}
        <a href="/api/example/docx">als Word</a>
      </dd>
    </dl>
  );
}
