# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A Qt5/C++11 client-server chat application with file sharing. Two independent Qt projects live under `Client/` and `Server/`, each with its own `.git` repo and `.pro` file.

## Build Commands

```bash
# Client (in Client/)
qmake Client.pro
make  # or mingw32-make on Windows

# Server (in Server/)
qmake Server.pro
make
```

No test suite or linter is configured.

## Architecture

**Communication protocol** — A custom binary protocol defined in `protocol.h` (both sides share identical copies). The `PDU` struct carries a fixed 64-byte `caData` header and a variable-length `caMsg` body. Message types are enumerated in `ENUM_MSG_TYPE` (regist, login, find user, add friend, chat, file operations, etc.).

**Singleton pattern** — `Client`, `Server`, `MyTcpServer`, and `OperateDB` are all singletons accessed via `getInstance()`.

### Client (`Client/`)

- `client.h/cpp` — Singleton managing the TCP connection (`QTcpSocket`). Sends PDUs via `sendMsg()`, receives and dispatches to `ResHandler::HandlerMsg()`. Loads IP/port/filesys-root from `client.config` (3 lines: IP, port, root path).
- `reshandler.h/cpp` — Processes every server response (`ENUM_MSG_TYPE_*_RESPOND`). Each handler reads fields from `PDU::caData`/`caMsg` and updates the appropriate UI widget. The main window is `client.ui`; sub-windows include `chat.ui`, `file.ui`, `friend.ui`, `index.ui` (login/register), `olineuser.ui`.

### Server (`Server/`)

- `server.h/cpp` — Entry point widget. Loads `client.config`, initializes the database singleton, starts `MyTcpServer`.
- `mytcpserver.h/cpp` — `QTcpServer` subclass. On `incomingConnection()`, creates a `MyTcpSocket`. Maintains a `QList<MyTcpSocket*>` for broadcasting/resending messages to specific users via `resend()`.
- `mytcpsocket.h/cpp` — `QTcpSocket` subclass. One instance per connected client. Reads PDUs in `recvMsg()`, dispatches to `MsgHandler::handleMsg()`, sends responses. Tracks `m_strLoginName` for user identity.
- `msghandler.h/cpp` — Request processor. Each method handles one request type (regist, login, add friend, chat, file operations) by calling `OperateDB` and constructing a response PDU.
- `operatedb.h/cpp` — Database singleton wrapping `QSqlDatabase` (MySQL). Handles user auth, friend relationships, online status. Connection is established in `connect()`.

### Current Issues

- `Client/main.cpp` has unresolved git merge conflict markers — the file currently includes both `client.h`/`index.h` (HEAD) and `server.h`/`operatedb.h` (merged branch). It won't compile until resolved.
- `Client/Server.pro` is a duplicate of `Server/Server.pro` — it does not belong in the Client directory.
