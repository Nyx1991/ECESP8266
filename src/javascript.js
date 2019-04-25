var x, g, j, t, i;
function initPage()
{		
    g = document.getElementById('gps');
    x = new XMLHttpRequest();
    x.onreadystatechange = function()
    {
        if (x.readyState == 4 && x.status == 200)
        {
            g.innerHTML = x.responseText;
            updatePage();
        }
    };
    x.open('GET', '/cmd?cmd=statushtml');
    x.send();                
}
function toggle(_g)
{
    x = new XMLHttpRequest();
    x.open('GET', '/cmd?cmd=toggle&gpio='+_g);
    x.send();
    updatePage();
}
function updatePage()
{
    if (t != null)
        clearTimeout(t);
    x = new XMLHttpRequest();
    x.onreadystatechange = function()
    {
        if (x.readyState == 4 && x.status == 200)
        {
            j = JSON.parse(x.responseText);
            for(i in j)
            {
                g = document.getElementById(j[0].GPIO);
                g.setAttribute('class', 'gpio '+j[0].ValueText);
                g.getElementsByClassName('gst')[0].innerHTML = j[0].ValueText;
            }
        }
    };
    x.open('GET', '/cmd?cmd=status');
    x.send();
    t = setTimeout(updatePage, 1500);
}
window.onload = initPage;