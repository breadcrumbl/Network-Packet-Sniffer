# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++20 -Wall -Wextra

# Project Directories
SRC_DIR = src
INCLUDE_DIR = include

# Npcap SDK Paths
NPCAP_DIR = /c/dev/npcap-sdk-1.16
NPCAP_INCLUDE = $(NPCAP_DIR)/Include
NPCAP_LIB = $(NPCAP_DIR)/Lib/x64

# Executable
TARGET = PacketSniffer.exe

# Source Files
# Finds every .cpp file inside of src/
SOURCES = 	$(wildcard $(SRC_DIR)/*.cpp) \
			$(wildcard $(SRC_DIR)/packetCapture/*.cpp) \
			$(wildcard $(SRC_DIR)/packetFormat/*.cpp) \
			$(wildcard $(SRC_DIR)/packetParser/*.cpp) \
			$(wildcard $(SRC_DIR)/packetPrinter/*.cpp)
			

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(NPCAP_INCLUDE) \
		$(SOURCES) \
		"$(NPCAP_LIB)/wpcap.lib" \
		"$(NPCAP_LIB)/Packet.lib" \
		-lws2_32 \
		-o $(TARGET)

# Remove Generated Executable
clean:
	rm -f $(TARGET)

# Targets that don't represent files
.PHONY: all clean