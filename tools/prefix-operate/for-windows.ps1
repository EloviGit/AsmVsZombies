function Add-PrefixToFiles {
    param([string]$Prefix)
    Get-ChildItem -File | ForEach-Object {
        Rename-Item $_.FullName ($Prefix + $_.Name)
    }
}
# 用法：Add-PrefixToFiles "myprefix_"

function Remove-PrefixFromFiles {
    param([string]$Prefix)
    Get-ChildItem -File | Where-Object { $_.Name.StartsWith($Prefix) } | ForEach-Object {
        Rename-Item $_.FullName ($_.Name.Substring($Prefix.Length))
    }
}
# 用法：Remove-PrefixFromFiles "myprefix_"