
# On-Screen Insert Key

This project is a simple Windows application that allows users to send the "Insert" key to a selected window from a list of currently visible windows. The application enumerates all visible windows, populates a combo box with their titles, and sends the "Insert" key to the selected window when a button is clicked.

## Features

- Enumerates and displays visible windows in a combo box.
- Sends the "Insert" key to the selected window.
- Simple and easy-to-use graphical interface.

## Getting Started

### Prerequisites

- Windows operating system
- Visual Studio or any compatible C++ development environment

### Building the Project

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/On-Screen-Insert-Key.git
   ```

2. Open the project in Visual Studio.

3. Build the project:
   - Select `Build` from the menu.
   - Click `Build Solution`.

### Running the Application

**Important:** The application must be run in administrator mode to function properly. This is because sending key inputs to other windows requires elevated privileges.

To run the application as an administrator:

1. Locate the executable file of the application or the Visual Studio project file.
2. Right-click the file.
3. Select "Run as administrator" from the context menu.
4. Confirm any prompts from the User Account Control (UAC) dialog to allow the application to run with elevated privileges.

### Usage

1. Launch the application as an administrator.
2. The combo box will be populated with the titles of currently visible windows.
3. Select a window from the combo box.
4. Click the "Insert" button to send the "Insert" key to the selected window.

## Code Overview

### Global Variables

- `CLASS_NAME`: The name of the window class.
- `WINDOW_TITLE`: The title of the window.
- `hwndComboBox`, `hwndButton`: Handles for the combo box and button.
- `windowHandles`: A vector to store the handles of the enumerated windows.

### Functions

- **EnumWindowsProc**: Callback function used by `EnumWindows` to enumerate all top-level windows.
- **PopulateComboBox**: Clears and repopulates the combo box and `windowHandles` vector.
- **SendInsertKeyToWindow**: Sends the "Insert" key to the specified window.
- **WindowProc**: Processes messages sent to the window.
- **wWinMain**: The entry point of the application.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

## Acknowledgments

- Inspiration from various Windows API examples and tutorials.
