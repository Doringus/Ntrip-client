# Ntrip-client
Simple ntrip client.
# Build instruction
## Requirements
- C++17 compatible compiler (tested on MSVC and G++)
- CMake
- Git
## Build and run
1. Clone repo:

`git clone https://github.com/Doringus/Ntrip-client.git`

2. Configure CMake:

`cmake .`

3. Build:

`cmake --build .`

4. Run

`./Ntrip_client`

## Example
Connect to ACACU mountpoint via RTK2GO caster

`./Ntrip_client -i 3.23.52.207:2101 -mp ACACU`

Client can write all incoming data in file:

`-o file.dat`
