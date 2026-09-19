# Buffer-IOT

Buffer-IOT is a small C exercise that stores outgoing IoT/MQTT-style messages
in a singly linked FIFO queue. Messages can be added while the network is
unavailable and sent in the same order after connectivity is restored.

## Features

- Stores a message ID, QoS level, topic, and payload.
- Assigns message IDs from the global counter, starting at `1001`.
- Appends new messages to the end of the queue.
- Sends and removes messages from the front of the queue.
- Handles an empty queue without dereferencing a null head pointer.

## Project Layout

```text
buffer.h          Message and linked-list definitions and public functions
buffer.c          Queue implementation
main.c            Example program that queues and sends messages
test/
	test_buffer.c   Unity-style unit tests
	test_main.c     Test runner
```

## API

```c
void save_message(Buffernode **head,
									const char *topic,
									const char *payload,
									uint8_t qos);

void send_message(Buffernode **head);
```

`save_message` appends a message to the queue. `send_message` prints the first
queued message and removes it. The caller owns the queue head pointer and must
pass its address to both functions.

## Build and Run

Compile the example from this directory with:

```sh
gcc -Wall -Wextra -std=c11 main.c -o buffer_iot
./buffer_iot
```

The example queues three messages, simulates network recovery, and then sends
messages until the queue is empty.

## Tests

The files in `test/` use the [Unity](https://github.com/ThrowTheSwitch/Unity)
test framework. After placing Unity's `unity.c` and `unity.h` where your
compiler can find them, the intended shape of the test command is:

```sh
gcc -Wall -Wextra -std=c11 \
		-I/path/to/Unity/src \
		buffer.c test/test_main.c /path/to/Unity/src/unity.c \
		-o buffer_iot_tests
./buffer_iot_tests
```

## Current Status

This is an instructional exercise and currently needs a small cleanup before
the example and tests build successfully:

- `buffer.c` needs `<stdlib.h>` for `malloc` and `free`.
- `buffer.c` contains a `prinf` typo that should be `printf`.
- The linked-list node type in `buffer.h` needs a self-referential declaration
	that uses the same `Buffernode` type consistently.
- The test assertions need to be aligned with the intended QoS, message ID,
	topic, and queue-state behavior.

Until those issues are fixed, the build commands above describe the intended
workflow rather than a currently passing build.
