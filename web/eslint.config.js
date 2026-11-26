// Lints the TypeScript code with the strictest typescript-eslint rules. Check: npm run lint
import eslint from "@eslint/js";
import reactHooks from "eslint-plugin-react-hooks";
import { defineConfig, globalIgnores } from "eslint/config";
import tseslint from "typescript-eslint";

export default defineConfig(
  globalIgnores(["dist"]),
  eslint.configs.recommended,
  tseslint.configs.strictTypeChecked,
  tseslint.configs.stylisticTypeChecked,
  reactHooks.configs.flat.recommended,
  {
    languageOptions: {
      parserOptions: {
        // This file is not in tsconfig.json, so it gets a default project.
        projectService: { allowDefaultProject: ["eslint.config.js"] },
      },
    },
  },
);
