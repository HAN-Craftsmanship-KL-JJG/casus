# Working agreements

How the team handles commits, branches, issues, pull requests and updates.
## C++ code conventions

1. Name each file after its class, as in the course examples: Opleiding.hpp, Opleiding.cpp, OpleidingTest.cpp.
Rename the existing files.

2. One .hpp and one .cpp file per class. An interface has only a .hpp file.

3. Write std:: in full. No using namespace in a header.

4. Plain [[nodiscard]] on queries. Add a reason only when ignoring the result causes a bug that the name does not show.

5. An interface has only a virtual destructor, with the clang-tidy option AllowSoleDefaultDtor.

6. Add a short "Where to put a new class" section to docs/layers.md.

## Pull requests during fysical meetings
When a pull request is created with a small update which everyone already saw, it is not required to request review before merging.

## Commit messages

Use [Conventional Commits](https://www.conventionalcommits.org/): `type(scope): subject`.
Example: `docs(domeinmodel): add Toetsmoment`.
Allowed types: `feat`, `fix`, `docs`, `refactor`, `test`, `perf`, `build`, `ci`, `chore`,
`style`, `revert`.
Link an issue in the footer with `Fixes #123` or `Refs #123`.

## Branches

We use [git flow](https://nvie.com/posts/a-successful-git-branching-model/).

![Git flow: feature, release and hotfix around main and develop](../.github/git-flow.svg)

| Branch | Starts from | Merges into | Purpose |
| --- | --- | --- | --- |
| `main` | | | Released versions only, each with a version tag |
| `develop` | | | Work for the next release |
| `feature/<topic>` | `develop` | `develop` | One change, through a pull request |
| `release/<version>` | `develop` | `main` and `develop` | Last fixes before a release |
| `hotfix/<topic>` | `main` | `main` and `develop` | An urgent fix |

Pull requests to `main` and `develop` need one approval and merge with a merge commit.
Git flow needs the merge commits, so `main` and `develop` keep a shared history.

## Releases

Versions follow [Semantic Versioning](https://semver.org/).

1. Start `release/<version>` from `develop`.
2. Set the version in `api/CMakeLists.txt`, `api/vcpkg.json`, `api/tests/status_test.cpp`,
   `documentserver/CMakeLists.txt`, `documentserver/vcpkg.json` and `web/package.json`.
   Run `npm install` in `web/` to update `web/package-lock.json`.
3. Open a pull request to `main` and one to `develop`.
4. After the merge to `main`, tag the merge commit: `git tag v<version>` and
   `git push origin v<version>`.
   The tag publishes a GitHub release with the PDF of the design document.

## Issues and pull requests

- Every issue gets a label: `documentation`, `enhancement` or `question`.
- A pull request names its issue with `Fixes #123`.
- Titles of issues and pull requests are in Dutch, commit messages in English.

## Dependency updates

Dependabot opens a pull request to `develop` each week when new versions exist.
Its settings are in `.github/dependabot.yml`.

| Kind | Where |
| --- | --- |
| GitHub Actions | `.github/workflows/` |
| Base images | The Dockerfiles in `api/`, `documentserver/` and `web/` |
| Container images | The Compose files in the root and in `infra/` |
| npm packages | `web/` |
| vcpkg packages | `builtin-baseline` in the two `vcpkg.json` files |

Review these pull requests like any other: the build must pass.
For a vcpkg pull request, set the vcpkg tag in the two Dockerfiles to the same version by hand.
