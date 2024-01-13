param([Parameter(ValueFromRemainingArguments=$true)][String[]]$Entries)

foreach ($Entry in $Entries) {
    if (-Not (Test-Path $Entry)) {
        New-Item -ItemType Directory -Name $Entry
    }
}