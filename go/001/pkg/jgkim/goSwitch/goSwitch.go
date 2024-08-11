package goSwitch

import "fmt"

var pop map[string]string

func init() {
	pop = make(map[string]string)
	pop["Adele"] = "Hello"
	pop["Alicia Keys"] = "Fallen'"
	pop["John Legend"] = "All of Me"
}

// GetMusic : Popular music by singer (외부에서 호출 가능)
func GetMusic(singer string) string {
	return pop[singer]
}

func getKeys() { // 내부에서만 호출 가능
	for _, kv := range pop {
		fmt.Println(kv)
	}
}

func Grade(score int) {
	switch {
	case score >= 90:
		println("A")
	case score >= 80:
		println("B")
	case score >= 70:
		println("C")
	case score >= 60:
		println("D")
	default:
		println("No Hope")
	}
}

func Sum(count int) int {
	sum := 0
	for i := 1; i <= count; i++ {
		sum += i
	}
	return sum
}
