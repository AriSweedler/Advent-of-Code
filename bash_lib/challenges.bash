function c::dir() {
  # Set some useful variables
  day00="${1:-$(date "+%d")}"
  day="$(printf "%d" "${day00}")"
  challenge_dir="${REPO_ROOT:?}/${YEAR}/challenges/${day00:?}"

  mkdir -p "${challenge_dir}"
}
