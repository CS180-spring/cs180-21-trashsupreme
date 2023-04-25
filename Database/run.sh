docker build . -t trashsupreme/backend:1.0
docker run -p 18080:8080 --platform linux/amd64 trashsupreme/backend:1.0