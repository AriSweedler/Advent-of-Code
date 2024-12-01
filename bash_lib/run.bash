function command::run() {
  c::dir "$@"
  cd "${challenge_dir}"
  cargo run
}
