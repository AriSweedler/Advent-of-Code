function command::answer() {
  local day00="${1:?}"
  local level="${2:?}"
  local ans="${3:?}"

  local day="$(printf "%d" "${day00}")"
  local challenge_dir="${REPO_ROOT:?}/challenges/${day00}"

  log::info "Submitting answer for day | day='${day}' level='${level}' ans='${ans}'"
  api --path "day/${day}/answer" --param "level=${level}" --param "answer=${ans}"

  # Check the output
  if ! [ -f "${OUTPUT}" ]; then
    log::err "Failed to get output?"
    exit 1
  fi

  if grep -q "You don't seem to be solving the right level." "${OUTPUT}"; then
    log::info "Wrong level - did you already solve?"
    exit 0
  fi

  if ! grep -q "That's the right answer" "${OUTPUT}"; then
    log::warn "Wrong answer"
    exit 1
  fi

  log::info "YAY!! Correct"
}
