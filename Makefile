compileRun:
	gcc producer.c -pthread -lrt -o producer
	gcc consumer.c -pthread -lrt -o consumer
	./producer & ./consumer &

compile:
	gcc producer.c -pthread -lrt -o producer
	gcc consumer.c -pthread -lrt -o consumer

run:
	./producer & ./consumer &
