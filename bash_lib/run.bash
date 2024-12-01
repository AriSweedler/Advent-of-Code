function command::run() {
  cd "${AOC_CDIR}"
  # Could use cargo's '-C' option on nightly - but let's not bother for now
  cargo run
}
