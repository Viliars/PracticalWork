class Point
{
 constructor(x,y)
 {
      this.x=x;
	  this.y=y;
 }
}


var array=[];
var el = document.getElementById('el');
el.addEventListener('click', getClickXY, false);
	
function cmp (a,b) {
	if (a.x<b.x) return -1;
	if((a.x == b.x) && (a.y < b.y)) return -1;
	if(a.x>b.x) return 1;
	if((a.x == b.x) && (a.y > b.y)) return 1;
	return 0;
}

function cw (a,b,c) {
	if (a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0) return 1;
	return 0;
}

function ccw (a,b,c) {
	if (a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0) return 1;
	return 0;
}
	
	
	
	 function convex_hull(hull)
	{
		var a=hull;
		if (a.length == 1) return a;
		a.sort(cmp);
		var p1 = new Point(a[0].x,a[0].y);
		var p2 = new Point(a[a.length-1].x,a[a.length-1].y);
		var up=[];
		var down=[];
		up.push(p1);
		down.push(p1);
		for(var i=1;i<a.length;i++)
		{
			if((i==a.length-1) || cw (p1, a[i], p2)) {
            while(up.length>=2)
                if (cw (up[up.length-2], up[up.length-1], a[i])==0) up.pop();
                else break;
            up.push(a[i]);
			}
        if((i==a.length-1) || ccw (p1, a[i], p2)) {
            while(down.length>=2)
                if (ccw ( down[down.length-2] , down[down.length-1], a[i])==0) down.pop();
                else break;
            down.push(a[i]);
			}
		}
		var bufer=[];
		for(var i=0;i<up.length;i++) bufer.push(up[i]);
		for(var i=down.length-2;i>0;i--) bufer.push(down[i]);
		return bufer;
	}	
	
	
	
function getClickXY(event)

  {
    var clickX = (event.layerX == undefined ? event.offsetX : event.layerX) + 1;

    var clickY = (event.layerY == undefined ? event.offsetY : event.layerY) + 1;
	
	if(clickX>=25&&clickX<=1003&&clickY>=25&&clickY<=742)
	{
	array.push(new Point(clickX-15,clickY-15));
	var buf=convex_hull(array);
	var i=0;
	var line;
	if(buf.length>2)
	{
		while((line=document.getElementById(i))!=null) { i++; line.remove(); }
		for(i=0;i<buf.length-1;i++)
		{
			line=document.createElementNS('http://www.w3.org/2000/svg', 'line');
			line.setAttributeNS(null,"x1",buf[i].x);
			line.setAttributeNS(null,"y1",buf[i].y);
			line.setAttributeNS(null,"x2",buf[i+1].x);
			line.setAttributeNS(null,"y2",buf[i+1].y);
			line.setAttributeNS(null,"stroke","black");
			line.setAttributeNS(null,"stroke-width","1");
			line.setAttributeNS(null,"id",i);
			document.querySelector("svg").appendChild(line);
		}
			line=document.createElementNS('http://www.w3.org/2000/svg', 'line');
			line.setAttributeNS(null,"x1",buf[0].x);
			line.setAttributeNS(null,"y1",buf[0].y);
			line.setAttributeNS(null,"x2",buf[i].x);
			line.setAttributeNS(null,"y2",buf[i].y);
			line.setAttributeNS(null,"stroke","black");
			line.setAttributeNS(null,"stroke-width","1");
			line.setAttributeNS(null,"id",i);
			document.querySelector("svg").appendChild(line);
	}
	circle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
	circle.setAttributeNS(null, "cx", clickX-15);
	circle.setAttributeNS(null, "cy", clickY-15);
	circle.setAttributeNS(null, "r", 3);
	circle.setAttributeNS(null, "fill", "red");
	document.querySelector("svg").appendChild(circle);
	}
  }