# Tarea 3 - Conexión C++ con PostgreSQL

## Objetivo
Establecer una conexión desde un programa en C++ hacia una base de datos PostgreSQL y ejecutar consultas básicas.

---

## Tecnologías utilizadas
- PostgreSQL
- pgAdmin
- C++
- libpqxx
- Visual Studio

---

## Instalación
Se instaló PostgreSQL junto con la herramienta de administración pgAdmin.

---

## Validación
Se verificó la conexión desde pgAdmin utilizando el usuario `postgres` y su contraseña.

Se ejecutó la siguiente consulta de prueba:

```sql
SELECT 1;
## Integración en C++

### Código principal

```cpp
#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        pqxx::connection C(
            "dbname=testdb user=postgres password=12345 host=localhost port=5432"
        );

        if (C.is_open()) {
            std::cout << "Conexion exitosa\n";
        }

        pqxx::work W(C);
        pqxx::result R = W.exec("SELECT * FROM usuarios");

        for (auto row : R) {
            std::cout << row["id"].as<int>() << " - "
                      << row["nombre"].as<std::string>() << std::endl;
        }

        W.commit();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
```
## Resultado
Conexion exitosa
1 - Andre