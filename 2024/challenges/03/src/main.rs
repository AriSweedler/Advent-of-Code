use std::env;
use std::fs::File;
use std::io::Read;
use std::process;

use logos::Logos;

#[derive(Logos, Debug, PartialEq)]
enum Token {
    // Fixed token "mul"
    #[token("mul")]
    Mul,

    // Fixed token "("
    #[token("(")]
    LParen,

    // Fixed token ")"
    #[token(")")]
    RParen,

    // Fixed token ","
    #[token(",")]
    Comma,

    // Regular expression for digits (matching any number)
    #[regex(r"[0-9]+")]
    Digit,
}

enum Program {
    CommandMult(i32, i32),
}

fn main() {
    // Determine the file path
    let file_path = env::args()
        .nth(1)
        .unwrap_or_else(|| "input.aoc".to_string());

    // Open the file
    let file = File::open(&file_path).unwrap_or_else(|_| {
        eprintln!("Error: Unable to open file '{}'", file_path);
        process::exit(1);
    });

    // Read the entire file content into a single string
    let mut file_content = String::new();
    file.take(90000) // Read the entire file
        .read_to_string(&mut file_content)
        .unwrap_or_else(|_| {
            eprintln!("Error: Unable to read file '{}'", file_path);
            process::exit(1);
        });

    // Tokenize the input string
    let tokens: Vec<Token> = Token::lexer(&file_content).collect();

    // Print the tokens
    for token in tokens {
        println!("{:?}", token);
    }

    // Our AST is just a vec
    let mut mult_me: Vec<(u32, u32)> = Vec::new();

    // Initialize the parser state
    let mut state = ParserState::Mult;
    let mut current_digits = String::new();

    // Iterate through each character in the file content
    let mut i = 0;
    while i < file_content.len() {
        let c = file_content.chars().nth(i).unwrap();
    }
}
