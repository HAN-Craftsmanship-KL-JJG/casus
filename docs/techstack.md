# Tech stack

The tools for the ICDE prototype, with the reason for each.
The prototype must work the same on macOS and Windows.

## Toolchain

| Tool | Purpose | Reason |
| --- | --- | --- |
| C++20 | Language | The team knows C++, and Clang and Drogon both support C++20 |
| Clang | Compiler | Works the same on macOS and Windows |
| CMake | Build system | Industry standard, used by Drogon and vcpkg |
| vcpkg | Package manager | Has every library in this list and works with CMake |

## Application server

| Tool | Purpose | Reason |
| --- | --- | --- |
| Drogon | Web framework: routing, sessions, database client | One library, so the least own code |
| jsoncpp | JSON | Part of Drogon |
| libsodium | Password hashing with Argon2id | Simplest safe API |

## Documents

| Tool | Purpose | Reason |
| --- | --- | --- |
| Pandoc | Word files from a template | Templates can change while running (UC10) |
| Typst | PDF files from a template | Fast, and one program |
| `pandoc/typst` | Image of the document server | Official image with both programs |

Pandoc and Typst run on their own document server, see
[Ontwerpkeuzes](design/09-ontwerpkeuzes.md#a2-waar-wordt-het-bestand-gemaakt).
A small C++ service with Drogon starts them, so the backend has one language and one framework.
The design document is built with the same three tools.

## Database

| Tool | Purpose | Reason |
| --- | --- | --- |
| PostgreSQL | Database server | Industry standard, and Drogon supports it best |

## API

| Tool | Purpose | Reason |
| --- | --- | --- |
| OpenAPI 3.1 | Contract of the REST API | Industry standard |
| Swagger UI | API documentation with calls from the browser | Helps testing while building |
| openapi-generator | TypeScript client from the contract | Keeps frontend and backend in step |

## Frontend and web server

| Tool | Purpose | Reason |
| --- | --- | --- |
| React with TypeScript | User interface | Widely used and easy to learn |
| Vite | Builds the frontend | Standard for React |
| Caddy | Serves the frontend and passes `/api` to Drogon | Simplest configuration |

## Tests

| Tool | Purpose | Reason |
| --- | --- | --- |
| GoogleTest | Unit tests | Industry standard |
| GoogleMock | Mocks, such as fake repositories | Part of GoogleTest |
| llvm-cov | Test coverage | Part of Clang |

## Code quality

| Tool | Purpose | Reason |
| --- | --- | --- |
| clang-tidy | Linter for C++ | Part of Clang, checks the C++ Core Guidelines |
| clang-format | Formatter for C++ | Part of Clang |
| ESLint | Linter for TypeScript | Industry standard |
| Prettier | Formatter for TypeScript | Industry standard |
| lizard | Limits on function complexity, length and parameters | One tool for C++ and TypeScript |
| GitHub CodeQL | Static analysis | Built into GitHub, free for a public repository |

## Deployment

| Tool | Purpose | Reason |
| --- | --- | --- |
| Docker Compose | Runs each server as its own container | Same on macOS, Windows and the server |
| GitHub Actions | Builds and tests every change | The repository is on GitHub |
| doco-cd | Deploys the Compose files to the server | One container |
| Dependabot | Weekly pull request for new versions | Built into GitHub, one file |
| Beszel | Monitoring of the server and its containers | Small, with its own login |
| Pocket ID | Accounts and passkeys for Beszel | Has a screen to manage users |

The servers follow [Architectuur](design/06-architectuur.md#architectuur).

## Optional

Login for ICDE itself through Pocket ID, in place of own login with libsodium.

| Tool | Purpose | Reason |
| --- | --- | --- |
| jwt-cpp | Checks the Pocket ID token in Drogon | Only needed with Pocket ID |
| `react-oidc-context` | Login through Pocket ID in the frontend | Only needed with Pocket ID |
