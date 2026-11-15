import react from "@vitejs/plugin-react";
import { defineConfig } from "vite";

export default defineConfig({
  plugins: [react()],
  server: {
    // `npm run dev` passes API calls on to the stack from `docker compose up`.
    proxy: { "/api": "http://localhost:8080" },
  },
});
