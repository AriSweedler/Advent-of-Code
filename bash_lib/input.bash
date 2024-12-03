function command::input() {
  local dest="${AOC_CDIR}/input.aoc"

  log::info "Getting input for day | day='${AOC_DAY}' dest='${dest#${REPO_ROOT}/}'"
  api --path "day/${AOC_DAY}/input" --output "${dest}"

  log::info "GOT N LINES OF INPUT | N='$(wc -l "${dest}" | awk '{print $1}')'"
}
