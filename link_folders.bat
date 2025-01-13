@echo off
for %%x in (components, render_techniques, renderers) do ^
for /f "tokens=*" %%F IN ('DIR %%x /AD /B') do ^
mklink /D %~dp0\Capsaicin\src\core\src\%%x\%%F %~dp0\%%x\%%F
