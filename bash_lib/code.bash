function command::code() {
  c::dir "$@"

  cd "${challenge_dir}"
  if ! [ -f "Cargo.toml" ]; then
    log::info "Initializing challenge"
    cargo init --name "c${AOC_0DAY}"
    cargo run
    command::input "${AOC_0DAY}"
    echo "# Day ${AOC_DAY}" > README.md
  fi
  "$EDITOR" "src/main.rs"
}
