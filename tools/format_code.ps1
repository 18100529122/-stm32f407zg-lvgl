# 定义 clang-format 可执行文件的路径
$clangFormatExe = "C:\work\github\-stm32f407zg-lvgl\tools\clang-format.exe"

# 定义要格式化的目录
$targetDirs = @(
    "C:\work\github\-stm32f407zg-lvgl\Core\BSP",
    "C:\work\github\-stm32f407zg-lvgl\Core\app"
)

Write-Host "Starting C/C++ code formatting..."

foreach ($dir in $targetDirs) {
    Write-Host "Processing directory: $dir"
    Get-ChildItem -Path $dir -Recurse -Include *.c, *.h | ForEach-Object {
        $filePath = $_.FullName
        Write-Host "Formatting file: $filePath"
        & $clangFormatExe -style=file -i $filePath
    }
}

Write-Host "C/C++ code formatting completed."