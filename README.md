<p align="center">
  <img src="https://img.shields.io/badge/FlexiStore-Manager-3B82F6?style=for-the-badge&logo=shoppingcart&logoColor=white" alt="FlexiStore Manager" height="50" />
</p>

<h1 align="center">🛒 FlexiStore Manager</h1>

<p align="center">
  <strong>نظام نقاط بيع متكامل (POS) لإدارة المتاجر — مدعوم بواجهة Flutter و باك‑إند C++ عالي الأداء</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Flutter-3.x-02569B?style=flat-square&logo=flutter&logoColor=white" alt="Flutter" />
  <img src="https://img.shields.io/badge/Dart-3.11-0175C2?style=flat-square&logo=dart&logoColor=white" alt="Dart" />
  <img src="https://img.shields.io/badge/C++-17-00599C?style=flat-square&logo=cplusplus&logoColor=white" alt="C++17" />
  <img src="https://img.shields.io/badge/MySQL-8.x-4479A1?style=flat-square&logo=mysql&logoColor=white" alt="MySQL" />
  <img src="https://img.shields.io/badge/CMake-3.20+-064F8C?style=flat-square&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/FFI-dart:ffi-8B5CF6?style=flat-square&logo=dart&logoColor=white" alt="FFI" />
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-333?style=flat-square&logo=windows&logoColor=white" alt="Platforms" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=flat-square&logo=opensourceinitiative&logoColor=white" alt="License" />
</p>

<p align="center">
  <em>A high-performance desktop POS & store management system — Flutter UI + native C++17 backend communicating via <code>dart:ffi</code>, powered by MySQL.</em>
</p>

---

## ✨ Overview

**FlexiStore Manager** is a **desktop-first** point-of-sale (POS) and store management application designed for retail businesses. It combines a sleek, modern **Flutter** front-end with a lightning-fast **C++17 native backend** compiled as a shared library (`flexistore.dll` / `.so` / `.dylib`) and accessed through Dart's **Foreign Function Interface (FFI)**.

> 🔑 **Why C++ + FFI?**  
> Instead of a traditional REST API or local SQLite, FlexiStore uses a compiled C++ shared library linked directly into the Flutter process. This eliminates network overhead, provides **near-zero latency** database operations, and delivers the raw performance of native code — all while keeping the beautiful, cross-platform Flutter UI.

---

## 🎯 Key Features

| Module | Feature | Description |
|:---:|---|---|
| 📊 | **Dashboard** | Real-time analytics with charts (revenue, top products, stock levels) via `fl_chart` |
| 🛒 | **Point of Sale (POS)** | Full-featured sales terminal with barcode support, cart management & invoice generation |
| 👥 | **Client Management** | Client profiles with phone, debt tracking, and transaction history |
| 📅 | **Installment Plans** | Flexible installment tracking — monthly payments, interest rates, progress monitoring |
| 📦 | **Inventory Management** | Product CRUD, stock tracking, barcode management, active/inactive status |
| 🔁 | **Returns & Refunds** | Process product returns linked to original invoices |
| 📜 | **Audit Trail** | Full transaction logs & inventory change history for accountability |
| 🔐 | **Authentication** | Role-based access control (Admin / Manager / Cashier) with hashed credentials |
| 🖨️ | **PDF Reports** | Generate and print invoices & reports using the `pdf` and `printing` packages |
| 🎨 | **Dark Mode UI** | Premium Material 3 dark theme with a polished sidebar navigation |

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────────────────────────────────┐
│                     Flutter Desktop App (Dart)                       │
│                                                                      │
│  ┌───────────┐ ┌─────┐ ┌─────────┐ ┌──────────────┐ ┌───────────┐  │
│  │ Dashboard  │ │ POS │ │ Clients │ │ Installments │ │ Inventory │  │
│  └─────┬─────┘ └──┬──┘ └────┬────┘ └──────┬───────┘ └─────┬─────┘  │
│        │          │         │              │               │          │
│        ▼          ▼         ▼              ▼               ▼          │
│  ┌──────────────────────────────────────────────────────────────┐    │
│  │           data/ layer — FFI Bindings (dart:ffi)              │    │
│  │     lookupFunction<CSignature, DartSignature>(...)           │    │
│  └────────────────────────────┬─────────────────────────────────┘    │
└───────────────────────────────┼──────────────────────────────────────┘
                                │  In-process function call
                                ▼
┌─────────────────────────────────────────────────────────────────────┐
│               Native Backend — flexistore.dll (C++17)                │
│                                                                      │
│  ┌───────────┐ ┌─────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐  │
│  │   auth/   │ │  pos/   │ │ clients/ │ │inventory/│ │  audit/  │  │
│  │  Session  │ │ Invoice │ │   CRUD   │ │  Stock   │ │   Logs   │  │
│  └─────┬─────┘ └────┬────┘ └────┬─────┘ └────┬─────┘ └────┬─────┘  │
│        │            │           │             │             │         │
│        ▼            ▼           ▼             ▼             ▼         │
│  ┌──────────────────────────────────────────────────────────────┐    │
│  │         core/ — MySQL Connector/C++ (libmysqlcppconn)        │    │
│  │              Connection Pool  ·  Query Builder               │    │
│  └──────────────────────────────┬───────────────────────────────┘    │
└─────────────────────────────────┼───────────────────────────────────┘
                                  │  TCP/Socket
                                  ▼
                        ┌───────────────────┐
                        │   MySQL 8.x DB    │
                        │   (flexistore)    │
                        └───────────────────┘
```

---

## 🗄️ Database Schema

The MySQL database `flexistore` contains the following tables:

| Table | Purpose |
|---|---|
| `users` | System users with roles (`admin`, `cashier`, `manager`) |
| `clients` | Customer profiles with debt tracking |
| `products` | Product catalog (barcode, prices, stock, status) |
| `invoices` | Sales invoices (cash, installment, return) |
| `invoice_items` | Line items linked to invoices and products |
| `installments` | Installment plans with monthly payment tracking |
| `installment_payments` | Individual payment records against installment plans |
| `inventory_logs` | Stock change audit trail |
| `transaction_logs` | Financial transaction audit trail |

> All tables use `InnoDB` with `utf8mb4` charset for full Unicode support (including Arabic).

---

## 🛠️ Tech Stack

### Frontend (Flutter Desktop)

| Technology | Purpose |
|---|---|
| **Flutter 3.x** | Cross-platform desktop UI framework |
| **Dart 3.11** | Programming language with null safety |
| **go_router** | Declarative routing with route guards |
| **fl_chart** | Beautiful, animated charts for the dashboard |
| **google_fonts** | Premium typography |
| **pdf** + **printing** | PDF invoice generation and printing |
| **dart:ffi** + **ffi** | Foreign Function Interface to call native C++ |
| **crypto** | Password hashing and security utilities |

### Backend (Native C++17)

| Technology | Purpose |
|---|---|
| **C++17** | High-performance native backend |
| **CMake 3.20+** | Cross-platform build system |
| **MySQL Connector/C++** | Database connectivity (libmysqlcppconn) |
| **Shared Library (.dll/.so)** | Compiled as `flexistore.dll` consumed via `dart:ffi` |

---

## 📁 Project Structure

```
flexistore_manager/
├── lib/                              # Flutter app source
│   ├── main.dart                     # Entry point — initializes FFI & runs app
│   ├── core/
│   │   ├── app_router.dart           # GoRouter routes with auth guard
│   │   ├── app_shell.dart            # Main layout (sidebar + top bar + content)
│   │   ├── sidebar_widget.dart       # Animated collapsible sidebar navigation
│   │   ├── native_bridge.dart        # Singleton FFI library loader
│   │   ├── ffi_helpers.dart          # JSON parse + memory free utilities
│   │   └── db_models.dart            # Dart models (Client, Product, Installment)
│   ├── auth/                         # 🔐 Login, session management
│   │   ├── data/                     # auth_ffi.dart, session_ffi.dart
│   │   ├── screens/                  # LoginScreen
│   │   └── widgets/                  # Auth UI components
│   ├── dashboard/                    # 📊 Analytics & KPI overview
│   │   ├── data/                     # Dashboard FFI data source
│   │   ├── screens/                  # DashboardScreen
│   │   └── widgets/                  # Charts, stat cards
│   ├── pos/                          # 🛒 Point of Sale terminal
│   │   ├── data/                     # POS FFI operations
│   │   ├── screens/                  # PosScreen
│   │   └── widgets/                  # Cart, product grid, invoice
│   ├── clients/                      # 👥 Client management
│   │   ├── data/                     # Clients FFI CRUD
│   │   ├── screens/                  # ClientsScreen
│   │   └── widgets/                  # Client forms, debt display
│   ├── installments/                 # 📅 Installment plans
│   │   ├── data/                     # Installments FFI
│   │   ├── screens/                  # InstallmentsScreen
│   │   └── widgets/                  # Payment tracking UI
│   ├── inventory/                    # 📦 Product & stock management
│   │   ├── data/                     # Inventory FFI
│   │   └── screens/                  # InventoryScreen
│   ├── returns/                      # 🔁 Returns & refunds
│   │   ├── data/                     # Returns FFI
│   │   ├── screens/                  # ReturnsScreen
│   │   └── widgets/                  # Return forms
│   └── audit/                        # 📜 Audit logs
│       ├── data/                     # Audit FFI queries
│       ├── screens/                  # TransactionsHistoryScreen, InventoryHistoryScreen
│       └── widgets/                  # Log tables, filters
│
├── backend_cpp/                      # Native C++17 backend
│   ├── CMakeLists.txt                # Build configuration
│   ├── flexistoreDB.sql              # Database schema & seed data
│   ├── cmake/                        # Custom CMake find modules
│   └── src/                          # C++ source code (mirrors Flutter modules)
│       ├── core/                     # DB connection, config, utilities
│       ├── auth/                     # Authentication & session logic
│       ├── audit/                    # Audit logging
│       ├── dashboard/                # Dashboard aggregation queries
│       ├── pos/                      # Sales & invoice processing
│       ├── clients/                  # Client CRUD operations
│       ├── inventory/                # Stock management
│       ├── installments/             # Installment plan logic
│       └── returns/                  # Return processing
│
├── web/                              # Web platform support
├── windows/                          # Windows runner configuration
├── pubspec.yaml                      # Flutter dependencies
└── analysis_options.yaml             # Dart lint rules
```

---

## 🚀 Getting Started

### Prerequisites

| Requirement | Version | Download |
|---|---|---|
| **Flutter SDK** | ≥ 3.x | [flutter.dev](https://docs.flutter.dev/get-started/install) |
| **Dart SDK** | ≥ 3.11 | Included with Flutter |
| **CMake** | ≥ 3.20 | [cmake.org](https://cmake.org/download/) |
| **MSVC / GCC / Clang** | C++17 support | Visual Studio / build-essential |
| **MySQL Server** | ≥ 8.x | [mysql.com](https://dev.mysql.com/downloads/) |
| **MySQL Connector/C++** | Latest | [mysql.com](https://dev.mysql.com/downloads/connector/cpp/) |

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/Fahd74/flexistore_manager.git
cd flexistore_manager
```

### 2️⃣ Setup the Database

```bash
# Login to MySQL and run the schema script
mysql -u root -p < backend_cpp/flexistoreDB.sql
```

This creates the `flexistore` database with all required tables and seed users:

| Username | Password | Role |
|---|---|---|
| `admin1` | `admin123` | Admin |
| `cashier1` | `123456` | Cashier |
| `store_mng` | `store123` | Manager |

### 3️⃣ Build the Native Backend

```bash
cd backend_cpp

# Configure with CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build the shared library
cmake --build build --config Release
```

This produces `flexistore.dll` (Windows) or `flexistore.so` (Linux) in `build/bin/`.

### 4️⃣ Deploy the DLL

Copy the compiled library to where the Flutter app can find it:

```bash
# Windows — copy to the Flutter build output directory
copy build\bin\flexistore.dll ..\build\windows\x64\runner\Release\
```

### 5️⃣ Run the Flutter App

```bash
# From the project root
cd ..
flutter pub get
flutter run -d windows
```

---

## 🔗 How FFI Works

The communication between Flutter and C++ follows this pattern:

```
┌──────────────────────┐         ┌──────────────────────┐
│      Dart (Flutter)   │         │    C++17 (Native)     │
│                       │         │                       │
│  NativeBridge()       │         │  flexistore.dll       │
│    .initialize()      │────────▶│                       │
│                       │         │                       │
│  lib.lookupFunction   │         │  extern "C" {         │
│    <CSignature,       │────────▶│    char* get_clients  │
│     DartSignature>    │         │    int  add_product   │
│    ('get_clients')    │         │    ...                 │
│                       │         │  }                    │
│  parseJsonAndFree()   │◀────────│  returns JSON string  │
│    → List<DbClient>  │         │  (heap allocated)     │
│                       │         │                       │
│  _freeFfiString(ptr)  │────────▶│  free_ffi_string(ptr) │
│  (prevents leaks)     │         │  (frees C++ heap)     │
└──────────────────────┘         └──────────────────────┘
```

1. **Load** — `NativeBridge` opens the platform-specific shared library
2. **Bind** — `lookupFunction` maps C exports to Dart callable functions
3. **Call** — Dart invokes native functions; C++ queries MySQL and returns JSON
4. **Parse** — `parseJsonAndFree()` converts the JSON to Dart models and frees native memory

---

## 🧑‍💼 Role-Based Access

| Permission | Admin | Manager | Cashier |
|---|:---:|:---:|:---:|
| Dashboard Analytics | ✅ | ✅ | ❌ |
| POS — Process Sales | ✅ | ✅ | ✅ |
| Inventory — Add/Edit Products | ✅ | ✅ | ❌ |
| Client Management | ✅ | ✅ | ✅ |
| Installment Plans | ✅ | ✅ | ❌ |
| Returns & Refunds | ✅ | ✅ | ❌ |
| Audit Logs | ✅ | ❌ | ❌ |
| User Management | ✅ | ❌ | ❌ |

---

## 🧪 Running Tests

```bash
# Flutter unit & widget tests
flutter test

# Build the C++ backend in debug mode for testing
cd backend_cpp
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

---

## 📸 Screenshots

> 🚧 *Screenshots coming soon — contributions welcome!*

<!--
<p align="center">
  <img src="screenshots/login.png" width="700" />
  <br/>
  <img src="screenshots/dashboard.png" width="700" />
  <br/>
  <img src="screenshots/pos.png" width="700" />
</p>
-->

---

## 🤝 Contributing

Contributions are welcome! Here's how to get started:

1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b feature/amazing-feature`
3. **Commit** your changes: `git commit -m 'Add amazing feature'`
4. **Push** to the branch: `git push origin feature/amazing-feature`
5. **Open** a Pull Request

### Development Guidelines

- Follow the established module structure (`data/`, `screens/`, `widgets/`)
- All C++ exports must use `extern "C"` with proper `__declspec(dllexport)`
- Always free native memory using `parseJsonAndFree()` — never leak heap allocations
- Use `DbModel.fromJson()` pattern for parsing native responses

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**Fahd** — [@Fahd74](https://github.com/Fahd74)

---

<p align="center">
  <strong>Built with ❤️ using Flutter + C++</strong>
  <br />
  <em>High-performance retail management, beautifully delivered.</em>
</p>
