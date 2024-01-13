param([Parameter(ValueFromRemainingArguments=$true)][String[]]$Entries)

foreach ($Entry in $Entries) {
    if (Test-Path $Entry) {
        Remove-Item -Recurse -Force $Entry
    }
}