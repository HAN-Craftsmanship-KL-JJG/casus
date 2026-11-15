import { StrictMode } from "react";
import { createRoot } from "react-dom/client";

import { App } from "./App";
import "./style.css";

const root = document.getElementById("root");
if (root === null) {
  throw new Error("Element #root is missing in index.html");
}

createRoot(root).render(
  <StrictMode>
    <App />
  </StrictMode>,
);
