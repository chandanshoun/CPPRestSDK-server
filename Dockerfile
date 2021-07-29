#use an existing docker image
FROM rest/updated-server

WORKDIR /home/app

CMD make Run
