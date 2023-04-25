export module Types {
export class Item {
    name: string = "";
    size: string = "";
    constructor(name: string, size: string) {
        this.name = name;
        this.size = size;
    }
}

export class Folder {
    name: string = "";
    folders: Folder[] = [];
    items: Item[] = [];
    isNew: boolean = false;
    constructor(name: string, folders: Folder[], items: Item[], isNew: boolean = false) {
        this.name = name;
        this.folders = folders;
        this.items = items;
        this.isNew = isNew;
    }
}
}