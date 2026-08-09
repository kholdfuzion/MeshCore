param(
    [string]$BuildDir = "E:\MC\mc_master\.pio\build",
    [switch]$Force
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $BuildDir -PathType Container)) {
    Write-Error "Build directory not found: $BuildDir"
}

# Check each immediate subdirectory for firmware.zip, then move+rename to <subdir>.zip in BuildDir.
$subdirs = Get-ChildItem -LiteralPath $BuildDir -Directory

if (-not $subdirs) {
    Write-Host "No subdirectories found in: $BuildDir"
    exit 0
}

$movedCount = 0
$skippedCount = 0

foreach ($dir in $subdirs) {
    $sourceZip = Join-Path -Path $dir.FullName -ChildPath "firmware.zip"

    if (-not (Test-Path -LiteralPath $sourceZip -PathType Leaf)) {
        continue
    }

    $destZip = Join-Path -Path $BuildDir -ChildPath ($dir.Name + ".zip")

    if ((Test-Path -LiteralPath $destZip -PathType Leaf) -and -not $Force) {
        Write-Warning "Skipping (destination exists): $destZip"
        $skippedCount++
        continue
    }

    Move-Item -LiteralPath $sourceZip -Destination $destZip -Force:$Force
    Write-Host "Moved: $sourceZip -> $destZip"
    $movedCount++
}

Write-Host "Done. Moved: $movedCount, Skipped: $skippedCount"
