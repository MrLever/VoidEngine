//Loads navigation menu into each page on wiki.
//Allows for central management of navigation
//This function does not work locally. Only on the server.
function loadNav(){
    console.log("Loading navigation");
    fetch('js/nav.html').then(
        function(response){
            if(response.status !== 200){
                console.log("Error loading file");
                return;
            }

            return response.text();
        }
    )
    .then(function(html){
        document.getElementById('NavDiv').innerHTML = html;
    })
    .catch(function(err){
        document.getElementById('NavDiv').innerHTML = 'oops, couldn\'t load navigation';
    });
}