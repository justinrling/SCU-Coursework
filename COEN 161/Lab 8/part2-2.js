// Implement a Binary Search Tree using JS Constructors and Pro
export class Node{    
    constructor(val){
        this.right = null;
        this.left = null;
        this.val = val;
    }
}

export class BinarySearchTree{
    constructor(){   
    this.root = null;
    }

    insert(x){
        var root = this.root;

        if(!root){		//initial node case
            this.root = new Node(x);
            return;
        }

        var currentNode = root;
        var newNode = new Node(x);

        while(currentNode){
            if(x < currentNode.val){	//value should be on left
                if(!currentNode.left){	//no left node, create new left  node
                    currentNode.left = newNode;
                    break;
                }
                else{	//if left node exists, keep traversing
                    currentNode = currentNode.left;
                }
            }
            else{	//value should be on the right
                if(!currentNode.right){		//no right node, create new right node
                    currentNode.right = newNode;
                    break;
                }
                else{	//if right node exists, keep traversing
                    currentNode = currentNode.right;
                }
            }	
        }
    }

    search(x){
        var currentNode = this.root;

        while(currentNode){
            if(x < currentNode.val){			//value is less than node
                currentNode = currentNode.left;
            }
            else if(x > currentNode.val){		//value is greater than node
                currentNode = currentNode.right;
            }
            else{	//value found
                return true;
            }
        }
        return false;	//if made it through loop without returning true
    }

    inorder(fn){
        var node = this.root;	//start at the root

        function order(x){
            if(x){		//go left, passed fn of current value, right
                order(x.left);
                fn(x.val);
                order(x.right);
            }
        }
        order(node);
    }
}

var bst = new BinarySearchTree();
// Uncomment this line to test your complete BST - make sure to pass a BST object created with the new keyword
