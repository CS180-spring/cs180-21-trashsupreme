export module Types {
export class Item {
    name: string = "";
    extention: string = "";
    content: string = "";
    docID: string = "-1";
    depth: number = 0;
    constructor(name: string, extention: string, content: string, docID: string, depth: number = 0) {
        this.name = name;
        this.extention = extention;
        this.content = content;
        this.docID = docID;
        this.depth = depth;
    }
}

export class Folder {
    name: string = "";
    folders: Folder[] = [];
    items: Item[] = [];
    isNew: boolean = false;
    depth: number = 0;
    constructor(name: string, folders: Folder[], items: Item[], isNew: boolean = false, depth: number = 0) {
        this.name = name;
        this.folders = folders;
        this.items = items;
        this.isNew = isNew;
        this.depth = depth
    }
}
}