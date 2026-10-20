# Qt 5.14.2 + MinGW 7.3.0 构建环境（serialplot Win7 版）
# 用法: 在 PowerShell 中执行  . D:\project\serialplot-0.13.0\qt5-env.ps1
# （新开的终端已通过用户级 PATH 自动生效，无需再执行本脚本）

$env:Path = 'D:\software\ware\qt\Tools\mingw730_64\bin;' +
            'D:\software\ware\qt\5.14.2\mingw73_64\bin;' +
            $env:Path

qmake -v
g++ --version | Select-Object -First 1
