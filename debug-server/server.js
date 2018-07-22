var http = require('http');

http.createServer(function (request, response) {
    let body = [];
    request.on('data', (chunk) => {
        body.push(chunk);
    }).on('end', () => {
        body = Buffer.concat(body).toString();
        const { headers, method, url } = request;
        console.log(url, method);
        console.log(headers);
        console.log(body);
        response.writeHead(200, { 'Content-type': 'text/plan' });
        response.write('');
        response.end();
    });

}).listen(8000);