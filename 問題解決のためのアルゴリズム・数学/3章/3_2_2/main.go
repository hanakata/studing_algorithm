package main

import "fmt"

func gcd(a int, b int) {
	for a >= 1 && b >= 1 {
		if a < b {
			b = b % a
		} else {
			a = a % b
		}
	}
	if a >= 1 {
		fmt.Println(a)
	} else {
		fmt.Println(b)
	}
}

func main() {
	gcd(33, 88)
}
