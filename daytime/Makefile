# Имя компилятора
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++11 -Wall

# Имена целей и их зависимости
CLIENT_TARGET = client
SERVER_TARGET = server

# Файлы исходного кода
CLIENT_SOURCE = client.cpp
SERVER_SOURCE = server.cpp

# Сборка клиента
$(CLIENT_TARGET): $(CLIENT_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_TARGET) $(CLIENT_SOURCE)

# Сборка сервера
$(SERVER_TARGET): $(SERVER_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(SERVER_TARGET) $(SERVER_SOURCE)

# Правило "clean" для удаления созданных файлов
clean:
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET)

# Правило "all" для сборки клиента и сервера
all: $(CLIENT_TARGET) $(SERVER_TARGET)

# Правило по умолчанию
.DEFAULT_GOAL := all

.PHONY: clean
