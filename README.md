<h1 align="center">missware</h1>

## Описание / Description

RU: Этот проект представляет собой консольное приложение с авторизацией через **Keyauth**. Приложение предоставляет различные функции и модификации игрового интерфейса.

EN: This project is a console application with authorization via **Keyauth**. The application provides various functions and modifications to the game interface.

### Реализованные функции / Implemented Features:
- **RU**: WallHack: позволяет видеть сквозь стены.
  
  **EN**: WallHack: allows you to see through walls.

- **RU**: Chams: выделяет персонажей и объекты яркими цветами.
  
  **EN**: Chams: highlights characters and objects with bright colors.

- **RU**: WallHack v2: Может работать лучше, чем Wallhack.
  
  **EN**: WallHack v2: May work better than Wallhack.

- **RU**: Delete Effects on Screen: убирает мешающие эффекты на экране для более комфортной игры.
  
  **EN**: Delete Effects on Screen: removes distracting screen effects for a better experience.

## Установка / Installation

RU:
1. Склонируйте репозиторий:
   ```bash
   git clone https://github.com/finnalynop/STALCRAFT-chams.git
   ```
2. Перейдите в папку проекта:
   ```bash
   cd STALCRAFT-chams
   ```

EN:
1. Clone the repository:
   ```bash
   git clone https://github.com/finnalynop/STALCRAFT-chams.git
   ```
2. Navigate to the project folder:
   ```bash
   cd STALCRAFT-chams
   ```

## Использование / Usage

RU:
1. Настройте проект в режиме Release x64.
2. Настройте Keyauth в коде:
   ```cpp
   std::string name = skCrypt("").decrypt(); // App name
   std::string ownerid = skCrypt("").decrypt(); // Account ID
   std::string secret = skCrypt("").decrypt(); // Application secret
   std::string version = skCrypt("").decrypt(); // Application version
   ```
3. Обновите оффсеты:
   ```cpp
   std::uintptr_t wallhackAddress = baseAddress + OFFSET;
   std::uintptr_t chamsAddress = baseAddress + OFFSET;
   ```
4. Запустите приложение:
   ```bash
   ./build/loader.exe
   ```

EN:
1. Configure the project in Release x64 mode.
2. Set up Keyauth in the code:
   ```cpp
   std::string name = skCrypt("").decrypt(); // App name
   std::string ownerid = skCrypt("").decrypt(); // Account ID
   std::string secret = skCrypt("").decrypt(); // Application secret
   std::string version = skCrypt("").decrypt(); //Application version
   ```
3. Update the offsets:
   ```cpp
   std::uintptr_t wallhackAddress = baseAddress + OFFSET;
   std::uintptr_t chamsAddress = baseAddress + OFFSET;
   ```
4. Run the application:
   ```bash
   ./build/loader.exe
   ```

## Скриншоты / Screenshots

<div align="center">
  <div>
	  <h2>RU: Пример работы WallHack / EN: Example of WallHack</h2>
	  <img src="https://i.ibb.co/H4dtCpL/wallhack.png" />
  </div>
  <div>
	  <h2>RU: Пример работы Chams / EN: Example of Chams</h2>
	  <img src="https://i.ibb.co/nnmWz42/chams.png" />
  </div>
</div>

## Зависимости / Dependencies

- **RU**: Keyauth SDK: для интеграции авторизации.
  
  **EN**: Keyauth SDK: for authorization integration.

- **RU**: skCrypt: библиотека для шифрования данных.
  
  **EN**: skCrypt: library for data encryption.

## Лицензия / License

RU: Этот проект распространяется под лицензией MIT. Подробности в файле [LICENSE](./LICENSE).

EN: This project is distributed under the MIT license. Details can be found in the [LICENSE](./LICENSE) file.

## Авторы / Authors

 ```
Dev - https://github.com/finnalynop
```

