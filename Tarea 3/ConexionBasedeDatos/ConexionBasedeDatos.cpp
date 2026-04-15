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

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}