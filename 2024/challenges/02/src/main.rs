use std::env;
use std::fs::File;
use std::io::{self, BufRead};

// Ghost type
type Report = Vec<u32>;

fn main() {
    // Determine the file path
    let file_path = env::args()
        .nth(1)
        .unwrap_or_else(|| "input.aoc".to_string());

    // Open the file
    let file = File::open(&file_path).unwrap_or_else(|_| {
        eprintln!("Error: Unable to open file '{}'", file_path);
        std::process::exit(1);
    });
    let handle = io::BufReader::new(file);

    // Create a Vec to store each report
    let mut reports: Vec<Report> = Vec::new();

    // Iterate through each line of input
    for line in handle.lines() {
        match line {
            Ok(l) => process_line(&l, &mut reports),
            Err(e) => eprintln!("Error reading line: {}", e), // Handle read error
        }
    }

    // For each report, check if it's good (1) or not (0). Sum that up
    let ans: u32 = reports.iter().map(|report| evaluate_report(report)).sum();
    println!("{}", ans)
}

fn process_line(line: &str, reports: &mut Vec<Report>) {
    // Split the line on whitespace and collect the parts into an iterator
    let parts: Vec<&str> = line.split_whitespace().collect();

    let parsed_parts: Vec<u32> = parts
        .iter()
        .map(|part| {
            part.parse::<u32>().unwrap_or_else(|_| {
                eprintln!("Error: '{}' is not a valid integer", part);
                std::process::exit(1);
            })
        })
        .collect();

    reports.push(parsed_parts);
}

fn evaluate_report(report: &Report) -> u32 {
    // Find the deltas between each next value in the report (minus scan)
    let deltas: Vec<i32> = report
        .windows(2)
        .map(|pair| pair[1] as i32 - pair[0] as i32)
        .collect();

    // Check to see if the deltas are all positive or all negative
    let d0 = deltas[0];
    if !deltas.iter().all(|&d| d * d0 >= 0) {
        // Unsafe report
        return 0;
    }

    // Check to make sure the deltas are not too large or too small
    if !deltas.iter().all(|&d| 1 <= d.abs() && d.abs() <= 3) {
        // Unsafe report
        return 0;
    }

    // Safe report
    1
}
