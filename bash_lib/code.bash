function command::code() {
  c::dir "$@"

  cd "${challenge_dir}"
  if ! [ -f "Cargo.toml" ]; then
    log::info "Initializing challenge"
    cargo init --name "c${day00}"
    cargo run
    command::input "${day00}"
    echo "# Day ${day}" > README.md
  fi
  "$EDITOR" "src/main.rs"
}
