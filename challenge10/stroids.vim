command! Stroids :source /Users/ari/dev/AoC/challenge10/stroids.vim | call Stroids()

" Terminate when we find a line that doesn't match "^[.#]\+$"

function! Stroids()
  " Loop through each line, reading into a 2D array
  let stroids = ReadStroids()
  let max = 0

  " Look at every asteroid, and see how many asteroids we can monitor there
  let lnum = 1
  for l in stroids
    let cnum = 1
    for c in l
      if c == '#'
        """"""""""""" " We're working with asteroids here: """""""""""""
        let mon_score = Monitor(stroids, lnum, cnum)
        if mon_score > max
          let max = mon_score
        endif
        """"""""""""""""""""""""""" " To here """"""""""""""""""""""""""
      endif
      let cnum = cnum + 1
    endfor
    let lnum = lnum + 1
  endfor

  " Return the max number of monitorable asteroids
  echom "The most number of asteroids we can monitor is " . max
endfunction

function! Monitor(stroids, lnum, cnum)
  " Look at every asteroid. Canonicalize it, and add it to the set
  " Canonicalize ==> x (int), y (int), spin (+ or -)
  let canonical_vectors = {}
  let lnum = 1
  for l in a:stroids
    let cnum = 1
    for c in l
      if c == '#'
        """"""""""""" " We're working with asteroids here: """""""""""""
        let ldiff = a:lnum - l:lnum
        let cdiff = a:cnum - l:cnum
        let [reduced, spin] = Canonicalize(ldiff, cdiff)
        let canonical_key = join(reduced, spin)
        let canonical_key = string(round(ldiff)/cdiff) . spin
        let sz1 = len(canonical_vectors)
        let canonical_vectors[canonical_key] = "(" . l:lnum . ", " . l:cnum . ")"
        let sz2 = len(canonical_vectors)
        let diff = "(" . ldiff . ", " . cdiff . ")"
        if sz1 == sz2
          echom diff . " blocked: " . canonical_vectors[canonical_key]
        else
          echom diff . " to " . canonical_vectors[canonical_key]
        endif
        echom
        """"""""""""""""""""""""""" " To here """"""""""""""""""""""""""
      endif
      let cnum = cnum + 1
    endfor
    let lnum = lnum + 1
  endfor

  "echom "For asteroid (" . a:lnum . ", " . a:cnum . "), we have: " . len(canonical_vectors) . " viewable directions:"
  return len(canonical_vectors)
endfunction

function! ReadStroids()
  let stroids = []
  let lnum = 1
  while lnum <= line("$")
    if getline(lnum) == ""
      break
    endif
    call add(stroids, split(getline(l:lnum), '\zs'))
    let lnum = lnum + 1
  endwhile
  return stroids
endfunction

"" Arguments to "setpos" = [bufnum, lnum, col, off]
"let upperLeft = [0, 1, 1, 0]
"call setpos(".", upperLeft)

" Returns a list [reduced, spin]
" * reduced is a list with 2 ints in it: [int, int]
" * spin is a char: '^' or 'v'
function! Canonicalize(x, y)
  let spin = (sin(round(a:x)/a:y) > 0)?"^":"v"
  let reduced = [a:x, a:y]
  return [reduced, spin]
endfunction
