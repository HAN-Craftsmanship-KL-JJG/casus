# Layers of the API

The API in `api/` follows the layers of the chapter Architectuur in the design document.
Each layer may use only the layers below it.
The domein then knows nothing about the database or HTTP.
You can test it without a database, and change the database without touching the domein.

The build checks these rules.
A wrong dependency between layers stops the build, so nobody breaks the rules by accident.
This file explains how.

## The layers

| Layer | Folder | Contains | May use |
| --- | --- | --- | --- |
| `domein` | `api/src/domein/` | Domain classes, business rules, repository interfaces | nothing |
| `applicatie` | `api/src/applicatie/` | The handlers, one per use case | `domein` |
| `datalaag` | `api/src/datalaag/` | The repositories that talk to PostgreSQL | `domein`, Drogon |
| `rest` | `api/src/rest/` | The REST endpoints | `applicatie`, Drogon, JsonCpp |

The repository interfaces belong to the `domein`, and the `datalaag` implements them.
So the `datalaag` depends on the `domein`, not the other way round
(Dependency Inversion Principle).

`api/src/main.cpp` is the only file that knows both `rest` and `datalaag`.
It creates the repositories and hands them to the handlers.
It contains no logic.

The namespaces follow the folders, such as `icde::domein`.
The tests follow them too, in `api/tests/<layer>/`.

## How the build checks the rules

`api/CMakeLists.txt` does all of this.

### One library per layer

Each layer is its own CMake library.
`target_link_libraries` lists the layers and packages it may use, and nothing else.

### Each layer sees only the headers it may use

Each library publishes only its own folder as include folder, such as `src/domein` for `domein`.
A library sees its own folder and the folders of the libraries it links.
`applicatie` links `domein`, so it sees `src/applicatie` and `src/domein`, and not `src/datalaag`.

A wrong include then fails to compile:

```text
src/applicatie/OpleidingHandler.cpp:2:10: fatal error: 'MockOpleidingRepository.hpp' file not found
```

### No include with ../

The compiler looks in the folder of the current file first.
`#include "../datalaag/MockOpleidingRepository.hpp"` would reach another layer and skip the
include folders.
CMake reads every file in `src/` and `tests/` and stops on any include with `../`:

```text
CMake Error at CMakeLists.txt:70 (message):
  /src/src/applicatie/OpleidingHandler.cpp: include a header by its name,
  without ../
```

### domein and applicatie link no packages

vcpkg puts the headers of all packages in one folder.
As soon as `domein` links one package, the Drogon headers in that folder are reachable too.
CMake therefore stops when `domein` links anything, or `applicatie` links anything but `domein`.

```text
CMake Error at CMakeLists.txt:60 (message):
  applicatie may link only domein, but links: domein;JsonCpp::JsonCpp
```

Without packages, a Drogon header in the `domein` fails to compile:

```text
src/domein/Opleiding.cpp:2:10: fatal error: 'drogon/drogon.h' file not found
```

## What the build does not check

Code review has to catch these.

- `rest` sees the headers of `domein`.
  The handlers return domain objects, so `rest` needs them.
  An endpoint must still go through a handler and never call a repository itself.
- `rest` links Drogon, and Drogon contains the database client.
  An endpoint must never run SQL itself.
  Only the `datalaag` talks to the database.

## Try it yourself

Build the API from the root of the repository:

```sh
docker build api
```

Then break a rule and build again.
For example, add `#include <drogon/drogon.h>` to `api/src/domein/Opleiding.cpp`.
The build stops with one of the errors above.
Undo the change afterwards.
