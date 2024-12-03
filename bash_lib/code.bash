function command::code() {
  cd "${AOC_CDIR}"
  if ! [ -f "Cargo.toml" ]; then
    log::info "Initializing challenge"
    cargo init --name "c${AOC_0DAY}"
    cargo run
    command::input "${AOC_0DAY}"
    echo "# Day ${AOC_DAY}" > README.md
  fi
  "$EDITOR" "src/main.rs"
}
