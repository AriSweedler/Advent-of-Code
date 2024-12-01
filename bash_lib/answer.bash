function command::answer() {
  local level="${1:?}"
  local ans="${2:?}"

  log::info "Submitting answer for day | day='${AOC_DAY}' level='${level}' ans='${ans}'"
  api --path "day/${AOC_DAY}/answer" --param "level=${level}" --param "answer=${ans}"

  # Check the output
  if ! [ -f "${API_OUTPUT_FILE}" ]; then
    log::err "Failed to get output?"
    exit 1
  fi

  if grep -q "You don't seem to be solving the right level." "${API_OUTPUT_FILE}"; then
    log::info "Wrong level - did you already solve?"
    exit 0
  fi

  if grep -q "That's the right answer" "${API_OUTPUT_FILE}"; then
    log::info "YAY!! Correct"
    exit 1
  fi

  log::warn "Wrong answer"
  sleep 3
  cat "${API_OUTPUT_FILE}"
  exit 1
}
