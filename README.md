# KTLT Project - Hệ Thống Quản Lý Sinh Viên

Hệ thống quản lý sinh viên và đăng ký môn học, xây dựng bằng C++ trên nền giao diện Console Windows.

---

## Tính Năng

| Vai Trò | Chức Năng |
|---|---|
| Giáo vụ (Staff) | Quản lý lớp, sinh viên, môn học, học kỳ, xem bảng điểm |
| Sinh viên (Student) | Đăng ký môn học, xem thời khóa biểu, xem điểm |

---

## Cấu Trúc Thư Mục

```
KTLT_Project/
|-- src/              <- Toàn bộ mã nguồn (.cpp)
|   |-- Main.cpp
|   |-- Menu.cpp
|   |-- Login.cpp
|   |-- AddStudent.cpp
|   |-- ChangeInfo.cpp
|   |-- ConsoleProcess.cpp
|   |-- CourseFunction.cpp
|   |-- ListClass.cpp
|   |-- ReadData.cpp
|   `-- StaffFunction.cpp
|
|-- include/          <- Khai báo header (.h)
|   |-- Struct.h
|   |-- ConsoleProcess.h
|   |-- Login.h
|   |-- Menu.h
|   |-- ReadData.h
|   |-- StaffFunction.h
|   |-- CourseFunction.h
|   |-- ListClass.h
|   |-- AddStudent.h
|   `-- ChangeInfo.h
|
|-- data/             <- Cơ sở dữ liệu CSV
|   |-- InformationOfLogin.csv
|   |-- InformationOfNewStudent.csv
|   |-- year_semester.csv
|   |-- SchoolYear/
|   `-- Score/
|
|-- KTLTProject.vcxproj
|-- KTLTProject.vcxproj.filters
|-- ProjectUpGithub.sln
|-- README.md
`-- .gitignore
```

---

## Hướng Dẫn Chạy Chương Trình

### Cách 1: Visual Studio (Khuyên dùng)

1. Mở file `ProjectUpGithub.sln` bằng Visual Studio 2019 hoặc 2022.
2. Nhấn `F5` hoặc click nút "Local Windows Debugger".

### Cách 2: Biên dịch và chạy bằng G++ từ terminal VS Code

Bước 1 - Biên dịch:
```bash
g++ src/*.cpp -I include/ -o App.exe
```

Bước 2 - Chạy chương trình:
```bash
conhost.exe .\App.exe
```

Lệnh `conhost.exe` sẽ mở một cửa sổ Console riêng biệt hỗ trợ đầy đủ giao diện màu sắc và bố cục của chương trình. Nếu chạy trực tiếp `.\App.exe` trong terminal của VS Code, giao diện sẽ bị lỗi hiển thị do VS Code không hỗ trợ đầy đủ Windows Console API.

---

## Tài Khoản Đăng Nhập Mẫu

Định dạng trong `Data/InformationOfLogin.csv`: `username,password,role,class`
- `role = 0`: Giáo vụ (Staff)
- `role = 1`: Sinh viên (Student)

| Vai Trò | Username | Password |
|---|---|---|
| Giáo vụ | `cqt` | `cqt` |
| Giáo vụ | `nkv` | `nkv` |
| Giáo vụ | `lhv` | `lhv` |
| Sinh viên | `20120001` | `20120001` |
| Sinh viên | `20171717` | `20171717` |

---

## Công Nghệ Sử Dụng

- Ngôn ngữ: C++ (C++11 trở lên)
- Môi trường: Windows OS (yêu cầu thư viện `<windows.h>`)
- IDE đề xuất: Visual Studio 2019 / 2022
- Dữ liệu: File CSV thuần túy (không dùng database)
