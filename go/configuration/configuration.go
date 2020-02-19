package main

import (
	"fmt"
	"io/ioutil"
	"log"

	"gopkg.in/yaml.v2"
)

const yamlconfigurationfile string = "config-example.yaml"

type Configuration struct {
	Path  string `yaml:"path"`
	Port  uint16 `yaml:"port"`
	Delay uint32 `yaml:"delay"`
}

func (configuration *Configuration) getConfiguration() *Configuration {
	yamlfile, err := ioutil.ReadFile(yamlconfigurationfile)
	if err != nil {
		log.Printf("Failed to open the configuration file: %v", err)
	}
	err = yaml.Unmarshal(yamlfile, configuration)
	if err != nil {
		log.Fatalf("Failed to unmarchal the configuration file: %v", err)
	}
	return configuration
}

func main() {
	var configuration Configuration

	configuration.getConfiguration()

	fmt.Println("Path:", configuration.Path)
	fmt.Println("Port:", configuration.Port)
	fmt.Println("Delay:", configuration.Delay)
}
