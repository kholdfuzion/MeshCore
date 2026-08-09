param(
    [string]$BuildDir = "E:\MC\mc_master\.pio\build",
    [switch]$Force
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $BuildDir -PathType Container)) {
    Write-Error "Build directory not found: $BuildDir"
}

# Check each immediate subdirectory for firmware.uf2, then move+rename to <subdir>.uf2 in BuildDir.
$subdirs = Get-ChildItem -LiteralPath $BuildDir -Directory

if (-not $subdirs) {
    Write-Host "No subdirectories found in: $BuildDir"
    exit 0
}

$movedCount = 0
$skippedCount = 0

foreach ($dir in $subdirs) {
    $sourceUf2 = Join-Path -Path $dir.FullName -ChildPath "firmware.uf2"

    if (-not (Test-Path -LiteralPath $sourceUf2 -PathType Leaf)) {
        continue
    }

    $destUf2 = Join-Path -Path $BuildDir -ChildPath ($dir.Name + ".uf2")

    if ((Test-Path -LiteralPath $destUf2 -PathType Leaf) -and -not $Force) {
        Write-Warning "Skipping (destination exists): $destUf2"
        $skippedCount++
        continue
    }

    Move-Item -LiteralPath $sourceUf2 -Destination $destUf2 -Force:$Force
    Write-Host "Moved: $sourceUf2 -> $destUf2"
    $movedCount++
}

Write-Host "Done. Moved: $movedCount, Skipped: $skippedCount"
