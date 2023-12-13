package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"unicode"
)

const LINE_LEN = 140

func main() {
	file, err := os.Open("input_day03.txt")

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	var array []string

	for scanner.Scan() {
		array = append(array, scanner.Text())
	}

	var indices [][2]int

	for _, line := range array {
		for index := 0; index < LINE_LEN; index++ {
			if unicode.IsDigit(rune(line[index])) {
				first_digit_index := index
				last_digit_index := index + 1

				if last_digit_index >= LINE_LEN-1 {
					indices = append(indices, [2]int{first_digit_index, last_digit_index})
				}

				for unicode.IsDigit(rune(line[last_digit_index])) {
					last_digit_index++
				}

				index = last_digit_index
				fmt.Printf("%d, %d\n", first_digit_index, last_digit_index)
			}

		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

}
