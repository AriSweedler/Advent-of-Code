function command::gh() {
  open "https://github.com/AriSweedler/aoc/${YEAR}"
}

function api() {
  # Required (and interesting) args
  if [ -z "${SESSION:-}" ]; then
    log::warn "Make sure you place your SESSION in the '.env' file"
    log::warn ".env path = '${REPO_ROOT}/.env'"
    exit 1
  fi
  local curl_args=(
    --header "cookie: session=${SESSION}"
    --header "referer: https://adventofcode.com/2024/day/${day}"
    --header "user-agent: AriSweedler AoC CLI"
  )

  # Parse args
  local path output key val
  while (( $# > 0 )); do
    case "$1" in
      --path) path="${2:?}"; shift 2 ;;
      --output) output="${2:?}"; shift 2 ;;
      --param) curl_args+=( --data-urlencode "${2:?}" ); shift 2 ;;
      --level|--answer)
        key="${1#--}"; val="${2:?}"; shift 2
        curl_args+=( --data-urlencode "${key}=${val}" )
        ;;
      *) echo "Unknown arg | func='${BASH_SOURCE[0]}' arg='$1'"; exit 1 ;;
    esac
  done

  # Required args
  if [ -z "${path:?}" ]; then
    log::err "Failed to provide a path to the API call"
    exit 1
  fi

  # Optional args (we have a fallback)
  : "${output:=$(mktemp /tmp/aoc${YEAR}.XXXXXX)}"

  # Boilerplate args
  curl_args+=(
    --header 'accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7'
    --header 'accept-language: en-US,en;q=0.9'
    --header 'cache-control: max-age=0'
    --header 'dnt: 1'
    --header 'priority: u=0, i'
    --header 'sec-ch-ua: "Not?A_Brand";v="99", "Chromium";v="130"'
    --header 'sec-ch-ua-mobile: ?0'
    --header 'sec-ch-ua-platform: "macOS"'
    --header 'sec-fetch-dest: document'
    --header 'sec-fetch-mode: navigate'
    --header 'sec-fetch-site: same-origin'
    --header 'sec-fetch-user: ?1'
    --header 'upgrade-insecure-requests: 1'
  )

  curl_args+=(
    --silent
    --output "${output}"
    --write-out "%{http_code}"
    --url "https://adventofcode.com/${YEAR}/${path}"
  )

  local http_code
  http_code="$(curl "${curl_args[@]}")"
  if (( 200 <= http_code )) && (( http_code < 300 )); then
    log::debug "Curl succeeded | curl_args='${curl_args[*]}'"
    export OUTPUT="${output}"
    return 0
  fi
  log::err "API request returned non-2xx | http_code='${http_code}'"
  log::err "DUMPING API RESPONSE OUTPUT -- START:"
  echo
  cat "${output}"
  echo
  log::err "DUMPING API RESPONSE OUTPUT -- END"
}
