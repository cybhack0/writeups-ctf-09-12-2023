package main

import (
	"fmt"
	"log"

	"vuln-web/internal/controller"
)

func main() {
	server, err := controller.ServerConstructor()

	if err != nil {
		log.Fatal(fmt.Errorf("failed to run server. ERROR: %w", err))
	}
	server.Run()
}
