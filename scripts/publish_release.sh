#!/bin/bash
#
# publish_release.sh - Create a GitHub release for XView with RPM assets
#
# Usage: ./publish_release.sh [-n] [-t TAG]
#   -n      Dry-run: show what would be done without actually doing it
#   -t TAG  Use a specific tag (default: auto-detect from spec file)
#
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_DIR="$(dirname "$SCRIPT_DIR")"
SPEC="$SCRIPT_DIR/XView.spec"
RPM_BASE="/export/shared/data/install/RedHat"

DRY_RUN=0
OVERRIDE_TAG=""

while getopts "nt:" opt; do
    case "$opt" in
        n) DRY_RUN=1 ;;
        t) OVERRIDE_TAG="$OPTARG" ;;
        *) echo "Usage: $0 [-n] [-t TAG]" >&2; exit 1 ;;
    esac
done

VERSION=$(grep '^Version:' "$SPEC" | awk '{print $2}')
RELEASE=$(grep '^Release:' "$SPEC" | sed 's/Release: *//; s/%{.*}//')
TAG="${OVERRIDE_TAG:-v${VERSION}-${RELEASE}}"

echo "=== XView Release Publisher ==="
echo "Version: $VERSION"
echo "Release: $RELEASE"
echo "Tag:     $TAG"
echo ""

RPMS=()
for RHEL in RHEL8 RHEL9; do
    RPM_DIR="$RPM_BASE/$RHEL/contrib/i386"
    SRPM_DIR="$RPM_BASE/$RHEL/contrib/SRPMS"
    DIST_TAG=".$(echo $RHEL | tr '[:upper:]' '[:lower:]' | sed 's/rhel/el/')"

    for rpm in "$RPM_DIR"/xview*-${VERSION}-${RELEASE}${DIST_TAG}.*.rpm; do
        [ -f "$rpm" ] || continue
        case "$rpm" in
            *debuginfo*|*debugsource*) continue ;;
        esac
        RPMS+=("$rpm")
    done

    for rpm in "$SRPM_DIR"/xview-${VERSION}-${RELEASE}${DIST_TAG}.src.rpm; do
        [ -f "$rpm" ] || continue
        RPMS+=("$rpm")
    done
done

if [ ${#RPMS[@]} -eq 0 ]; then
    echo "ERROR: No RPMs found for $VERSION-$RELEASE"
    echo "Build RPMs first with build_rpms.sh"
    exit 1
fi

echo "Found ${#RPMS[@]} RPM(s) to upload:"
for rpm in "${RPMS[@]}"; do
    echo "  $(basename "$rpm")"
done
echo ""

cd "$REPO_DIR"

CHANGELOG=$(sed -n '/^%changelog/,/^%[a-z]/p' "$SPEC" | \
    sed '1d;/^%[a-z]/d' | \
    awk '/^\*/{if(n++)exit}1')

if [ "$DRY_RUN" -eq 1 ]; then
    echo "[DRY RUN] Would create tag: $TAG"
    echo "[DRY RUN] Would create release with ${#RPMS[@]} assets"
    echo "[DRY RUN] Release notes:"
    echo "$CHANGELOG"
    exit 0
fi

if ! git rev-parse "$TAG" >/dev/null 2>&1; then
    echo "Creating tag $TAG..."
    git tag -a "$TAG" -m "XView $VERSION release $RELEASE"
    git push origin "$TAG"
else
    echo "Tag $TAG already exists"
fi

if gh release view "$TAG" >/dev/null 2>&1; then
    echo "Release $TAG already exists, uploading new assets..."
    gh release upload "$TAG" "${RPMS[@]}" --clobber
else
    echo "Creating release $TAG..."
    gh release create "$TAG" \
        --title "XView ${VERSION}-${RELEASE}" \
        --notes "## XView $VERSION release $RELEASE

$CHANGELOG
" \
        "${RPMS[@]}"
fi

echo ""
echo "Release published: https://github.com/ElCoyote27/XView/releases/tag/$TAG"
